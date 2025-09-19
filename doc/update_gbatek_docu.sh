#!/bin/bash

INPUT_NAME="GBATEK-GBA_NDS_Technical_Info"
INPUT_FORMAT=".html"
INPUT_FILE="$INPUT_NAME$INPUT_FORMAT"
UTF8_FILE="gbatek_utf8.html"
OUTPUT_FILE="$INPUT_NAME.md"
TEMP_FILE="temp_chapter.md"

chapter_name=""
headline=""
chapter_detected=false
chapter_end=false
chapter_started=false
table_detected=false
headline_detected=false

if command -v wget >/dev/null 2>&1; then
    printf "Command wget is available... \n\n"
else
    sudo apt-get install wget
fi

if command -v pandoc >/dev/null 2>&1; then
    printf "Command pandoc is available... \n\n"
else
    sudo apt-get install pandoc
fi

printf "Get $INPUT_FILE... \n\n"
wget -O "$INPUT_FILE" http://www.problemkaputt.de/gbatek.htm

printf "Convert $INPUT_FILE to UTF-8...\n"
iconv -f ISO-8859-1 -t UTF-8 "$INPUT_FILE" -o "$UTF8_FILE"

printf "Convert HTML into Markdown...\n\n"
pandoc "$UTF8_FILE" -f html -t markdown --wrap=none -o "$OUTPUT_FILE"

rm -rf "./tmp"
mkdir ./tmp

printf "Extract all chapters from Markdown...\n"
total=$(wc -l < "$OUTPUT_FILE")
current=0
last_percent=-1

while IFS= read -r line; do
    ((current++))
    percent=$((current * 100 / total))

    if (( percent != last_percent )); then
        last_percent=$percent

        bar_length=30
        filled_length=$((percent * bar_length / 100))
        empty_length=$((bar_length - filled_length))

        bar=$(printf "%0.s#" $(seq 1 $filled_length))
        empty=$(printf "%0.s " $(seq 1 $empty_length))

        printf "\r[%s%s] %3d%% - Process Line %d of %d" "$bar" "$empty" "$percent" "$current" "$total"
    fi

    if [[ "$line" =~ ^\ {2}-+$ ]]; then
        chapter_end=true
    
        if $chapter_started; then
            mv "$TEMP_FILE" "./tmp/$chapter_name.md"
            rm -f "$TEMP_FILE"
            chapter_detected=false
            chapter_started=false
        fi
        continue
    fi

    if [[ -n $chapter_detected ]] && [[ "$line" =~ \[\]\{#([a-zA-Z0-9_-]+)\} ]]; then
        chapter_name="${BASH_REMATCH[1]}"
        line="${line#*\}}"
        echo "#$line" >> "$TEMP_FILE"
        chapter_detected=true
        continue
    fi
    
    if [[ "$line" == *"\\"* ]]; then
        line="${line::-1}"
    fi

    if $chapter_detected; then
        if [[ -n $chapter_started ]]; then
            chapter_started=true
        fi

        if [[ "$line" == *"](#"* && "$line" != *"|"* ]]; then
            fragment=$(echo "${line#*#}" | sed 's/[)\\]*$//')
            filename="./${fragment}.md"

            tmp="${line#*[}"
            result="${tmp%%]*}"

            line="- [$result]($filename)"

            echo "$line" >> "$TEMP_FILE"
        elif [[ "$line" == *"+--"* ]]; then
            if $table_detected; then
                echo "$line" >> "$TEMP_FILE"
                echo "\`\`\`" >> "$TEMP_FILE"
                table_detected=false
            else
                echo "\`\`\`" >> "$TEMP_FILE"
                echo "$line" >> "$TEMP_FILE"
                table_detected=true
            fi
        elif [[ "$line" == *"**"* ]]; then
            count=$(echo "$line" | tr -cd '*' | wc -c)

            if [[ "$count" -ge 4 ]]; then
              tmp=$(echo "$line" | sed -n 's/^.*\*\*\(.*\)\*\*.*$/\1/p')
              line="### $tmp"
              echo "$line" >> "$TEMP_FILE"
            else
              if $headline_detected; then
                tmp="$headline $line"
                tmp=$(echo "$tmp" | sed -n 's/^.*\*\*\(.*\)\*\*.*$/\1/p')
                headline_detected=false

                line="### $tmp"
                echo "$line" >> "$TEMP_FILE"
              else
                headline="$line"
                headline_detected=true
              fi
            fi
        else
            echo "$line" >> "$TEMP_FILE"
        fi
    fi
done < "$OUTPUT_FILE"

if $chapter_started && [[ -n "$chapter_name" ]]; then
    mv "$TEMP_FILE" "./tmp/$chapter_name.md"
fi

printf "\nExtract all chapter references files...\n\n"
for file in $(find ./tmp -type f -name '*reference*'); do
    filename=$(basename "$file")

    rm ./$filename

    while IFS= read -r line; do
        if [[ "$line" == *"](."* ]]; then        
            line="${line/.\//.\/tmp\/}"
        fi
        echo "$line" >> "./$filename"
    done < "$file"
    
    rm "$file"
done

rm "./tmp/contents.md"
rm "$OUTPUT_FILE"
rm "$UTF8_FILE"
rm "$INPUT_FILE"
rm -f "$TEMP_FILE"