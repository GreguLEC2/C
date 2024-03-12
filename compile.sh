#!/bin/bash

# Find all C files recursively in subdirectories
find . -name '*.c' | while read file; do
    if [ -f "$file" ]; then
        filename=$(basename "$file" .c)
        output_path=$(dirname "$file")

        # Detect platform (Assuming GNU/Linux and Windows for simplicity)
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            clang -o "${output_path}/${filename}" "$file" -lm
        elif [[ "$OSTYPE" == "msys"* ]] || [[ "$OSTYPE" == "win32" ]]; then
            clang -o "${output_path}/${filename}.exe" "$file"
        else
            echo "Unsupported OS: $OSTYPE"
            exit 1
        fi

        if [ $? -eq 0 ]; then
            echo "Compilation successful for $file"
        else
            echo "Error compiling $file"
            exit 1 # Exit the pipeline with a non-zero status code
        fi
    fi
done
