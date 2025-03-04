#!/bin/bash

SOURCE_FOLDER="../include/pragma"
OUTPUT_FOLDER="../single_include/pragma"
OUTPUT_FILE="$OUTPUT_FOLDER/log.hpp"

# Crea la cartella di destinazione se non esiste
mkdir -p "$OUTPUT_FOLDER"

# Svuota il file di output se esiste già
> "$OUTPUT_FILE"

# Aggiungi #pragma once all'inizio del file di output
echo "#pragma once" >> "$OUTPUT_FILE"
echo -e "\n" >> "$OUTPUT_FILE"

# Collect all #include directives excluding those with .hpp or enclosed in double quotes
INCLUDES=$(find "$SOURCE_FOLDER" -type f -name "*.hpp" -exec grep -hE "^#include" {} + | grep -vE "\".*\.hpp\"" | sort | uniq)

# Add all #include directives at the top
if [ -n "$INCLUDES" ]; then
    echo "$INCLUDES" >> "$OUTPUT_FILE"
    echo -e "\n" >> "$OUTPUT_FILE"
fi

# Variabile lista con l'ordine desiderato dei file
FILE_LIST=(
    "log/pattern_utils.hpp"
    "log/logging_pattern.hpp"
    "log/utils.hpp"
    "log/logging_category.hpp"
    "log/logging_registry.hpp"
    "log/logging_target.hpp"
    "log/base_logger.hpp"
    "log/info_logger.hpp"
    "log/debug_logger.hpp"
    "log/warning_logger.hpp"
    "log/error_logger.hpp"
    "log.hpp"
)

for file in "${FILE_LIST[@]}"; do
    echo "// File: $file" >> "$OUTPUT_FILE"
    if [ -f "$SOURCE_FOLDER/$file" ]; then
        grep -Ev "^#pragma once|^#include" "$SOURCE_FOLDER/$file" >> "$OUTPUT_FILE"
    else
        echo "// $file not found" >> "$OUTPUT_FILE"
    fi
    echo -e "\n" >> "$OUTPUT_FILE"
done

echo "File created at: $OUTPUT_FILE"





























# # #!/bin/bash


# # SOURCE_FOLDER="../src"
# # OUTPUT_FOLDER="../single_include/pragma"
# # OUTPUT_FILE="$OUTPUT_FOLDER/log.hpp"

# # # Create the destination folder if it does not exist
# # mkdir -p "$OUTPUT_FOLDER"

# # # Empty the output file if it already exists
# # > "$OUTPUT_FILE"

# # # Add #pragma once at the beginning of the output file
# # echo "#pragma once" >> "$OUTPUT_FILE"
# # echo -e "\n" >> "$OUTPUT_FILE"

# # # Collect all #include directives excluding those with .hpp or enclosed in double quotes
# # INCLUDES=$(find "$SOURCE_FOLDER" -type f -name "*.hpp" -exec grep -hE "^#include" {} + | grep -vE "\".*\.hpp\"" | sort | uniq)

# # # Add all #include directives at the top
# # if [ -n "$INCLUDES" ]; then
# #     echo "$INCLUDES" >> "$OUTPUT_FILE"
# #     echo -e "\n" >> "$OUTPUT_FILE"
# # fi

# # # Add header separators and pragma_log.hpp file at the top
# # echo "/************** FUNDAMENTAL COMMANDS **************/" >> "$OUTPUT_FILE"
# # echo "// File: pragma_log.hpp" >> "$OUTPUT_FILE"
# # if [ -f "$SOURCE_FOLDER/pragma_log.hpp" ]; then
# #     grep -Ev "^#pragma once|^#include" "$SOURCE_FOLDER/pragma_log.hpp" >> "$OUTPUT_FILE"
# # else
# #     echo "// pragma_log.hpp not found" >> "$OUTPUT_FILE"
# # fi
# # echo "/************** END FUNDAMENTAL COMMANDS **************/" >> "$OUTPUT_FILE"
# # echo -e "\n" >> "$OUTPUT_FILE"
# # echo -e "\n" >> "$OUTPUT_FILE"
# # echo -e "\n" >> "$OUTPUT_FILE"


# # echo "// File: patterns/pattern_utils.hpp" >> "$OUTPUT_FILE"
# # if [ -f "$SOURCE_FOLDER/pattern_utils.hpp" ]; then
# #     grep -Ev "^#pragma once|^#include" "$SOURCE_FOLDER/pattern_utils.hpp" >> "$OUTPUT_FILE"
# # else
# #     echo "// pattern_utils.hpp not found" >> "$OUTPUT_FILE"
# # fi

# # # Find all .hpp files recursively and concatenate them into the output file without #pragma once or #include
# # find "$SOURCE_FOLDER" -type f -name "*.hpp" | sort | while read -r file; do
# #     if [ "$file" != "$SOURCE_FOLDER/pragma_log.hpp" ]; then
# #         echo "// File: $file" >> "$OUTPUT_FILE"
# #         grep -Ev "^#pragma once|^#include" "$file" >> "$OUTPUT_FILE"
# #     fi
# # done

# # echo "File unito creato in: $OUTPUT_FILE"