# Music Management System (MMS)
Set of file reading and writing tools I use to manage my personal music collection.

## Upcoming Features:
 - Support for renaming album artist metadata
 - Support for non-ASCII characters

## Version History:

### v1
 - file_reader.cpp
    - usage: directory path, output file
    - reads all files in specified directory and outputs to file
 - file_editor.cpp
    - usage: directory path, tsv file
    - modifies all files in specified directory as specified by tsv
    - tsv file
       - the tsv file must have the following columns in the specified order:
          - Original File Name
          - New File Name
          - Name
          - Track Number
          - Title
          - English Title
          - Contributing Artist
          - Album
          - Album Artist
          - Genre
          - Year
       - The first row has to be the above column headers

Known Issues:
 - Renaming the album artist name doesn't work
 - Using non-ASCII characters in may not work
 - Not an issue, but remember Windows does not allow / in file names
