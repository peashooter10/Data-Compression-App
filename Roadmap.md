# Roadmap
## Purpose and functionality
The application has the main role of compressing files in a _lossless_ format, the resulting file being smaller in size, but the quality remains the same after the procces of decompression. It is a Windows Desktop Application that implements the Huffman algorithm .
To exemplify the _lossless_ compression, the string "AAABCDDD" can be compressed, transforming into "3ABC3D". Therefore, the compressed file can be reverted into the original file.
In contrast, a song that is compressed may lose some unique and harder to spot musical notes of the singer or the instrument. However, reverting the file to its original state is impossibile as those characteristics are lost forever.

## Development
The following application will be developed in Visual Studio Code 2026 in C++ 20 for the implementation of the compression algorithm, then Qt for the GUI.

## The market
In today's market, there are a range of apps that specialise in the compression of data, the most known being WinRAR or 7Zip, both with similar interfaces and functionalities.

## Planning
Week 1: Roadmap, analysis of the problem, selecting the environment to develop the app, console implementation of the Huffman algorithm, both compression and decompression\
Week 2: Creating the basic console application with buttons and user-friendly GUI, mplementation of a simple code in order to test the functionality of the console application\
Week 3: Developing the script to choose a file from the Windows File Explorer and print a preview in the console to check if it is working\
Week 4: Merging the Qt app with the Huffman c++ compression and decompression algorithms\
Week 5: Testing the app for a range of text file formats, from CSV to TXT\
Week 6 and on: Development and testing future ideas
