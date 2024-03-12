#!/bin/bash

rename_files_recursively() {
    find . -type f -name '*.cpp' | while read -r file; do
        relative_path=$(dirname "$file")
        newname="$relative_path/$(basename "$file" .cpp).c"
        mv "$file" "$newname"
        echo "Renamed: $file to $newname"
    done
}

remove_polish_characters() {
    find . -depth -name '*[ąćęłńóśźżĄĆĘŁŃÓŚŹŻ]*' | while read -r file; do
        newname=$(echo "$file" | iconv -f UTF-8 -t ASCII//TRANSLIT | sed 'y/ąćęłńóśźżĄĆĘŁŃÓŚŹŻ/acelnoszzACELNOSZZ/')
        mv "$file" "$newname"
        echo "Renamed: $file to $newname"
    done
}

replace_space_with_underscore_in_directories() {
    find . -depth -type d -name '* *' | while read -r directory; do
        newname=$(echo "$directory" | tr ' ' '_')
        mv "$directory" "$newname"
        echo "Renamed directory: $directory to $newname"
    done
}

replace_space_with_underscore_in_files() {
    find . -depth -type f -name '* *' | while read -r file; do
        newname=$(echo "$file" | tr ' ' '_')
        mv "$file" "$newname"
        echo "Renamed file: $file to $newname"
    done
}

rename_files_recursively
remove_polish_characters
replace_space_with_underscore_in_directories
replace_space_with_underscore_in_files
