#!/bin/bash

INPUT_NAME="GBATEK-GBA_NDS_Technical_Info"
INPUT_FORMAT=".html"
INPUT_FILE="$INPUT_NAME$INPUT_FORMAT"
UTF8_FILE="gbatek_utf8.html"
OUTPUT_FILE="$INPUT_NAME.md"
TEMP_FILE="temp_chapter.md"

chapter_name=""
chapter_detected=false
chapter_end=false
chapter_started=false
table_detected=false

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

printf "Convert $INPUT_FILE to UTF-8...\n\n"
file -i "$INPUT_FILE"
iconv -f US-ASCII -t UTF-8 "$INPUT_FILE" -o "$UTF8_FILE"

printf "Convert HTML into Markdown...\n\n"
pandoc -f html -t markdown -o "$OUTPUT_FILE" "$UTF8_FILE"

rm "$UTF8_FILE"
rm "$INPUT_FILE"
rm -f "$TEMP_FILE"

rm -rf "./tmp"
mkdir ./tmp

printf "Extract all chapters from Markdown...\n"
total=$(wc -l < "$OUTPUT_FILE")
current=0

while IFS= read -r line; do
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
    
    if [[ "$line" == *"["* ]]; then
        line="- $line"
    fi

    if $chapter_detected; then
        if [[ -n $chapter_started ]]; then
            chapter_started=true
        fi

        if [[ "$line" == *"](#"* ]]; then    
            if [[ "$line" != *"["* ]]; then
                truncate -s -1 "$TEMP_FILE"
            fi
            
            fragment=$(echo "${line#*#}" | sed 's/[)\\]*$//')
            filename="./${fragment}.md"
            new_line="${line%%(*}"
            
            line="$new_line($filename)"
            
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
        else
            echo "$line" >> "$TEMP_FILE"
        fi
    fi
    
    ((current++))
    percent=$((current * 100 / total))
    printf "\rProcess Line %d of %d (%d%%)" "$current" "$total" "$percent"
done < "$OUTPUT_FILE"

if $chapter_started && [[ -n "$chapter_name" ]]; then
    mv "$TEMP_FILE" "./tmp/$chapter_name.md"
fi

printf "\nExtract all chapter references files...\n\n"
for file in $(find ./tmp -type f -name '*reference*'); do
    filename=$(basename "$file")

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
