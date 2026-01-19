File scanner: The file scanner takes any file path you provide and scans the contents of the directory. After scanning, it will output the command, such as the size of the directory. If the directory has subdirectories, it will recursively call the CalculateSize function until it has scanned all the subdirectories and the main one. Each subdirectory is calculated and displayed, and then added up to a total, which is displayed at the end. 

Usage: ./filescanner [directory]

         Main
          |
          | calls 
          |
    Calculate total <-|
         |            |
         |____________|
         |
   outputs total