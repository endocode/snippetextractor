# How to extract snippets from source code and add them to Markdown articles

Samples copy-pasted from application code will invariably go stale and be out of date. Such duplication is avoided by retrieving the code samples from the application code and inserting them into the Markdown documents when needed. SnippetExtractor is a filter program implementing this functionality. 

## Building, installing and running

SnippetExtractor is written in C++ and uses the Qt framework. It uses the QMake build system. The program takes two parameters, the input and the output file: 

~~~ 
: > snippetextractor article.md.in article.md
~~~

## Markup of code samples

Code samples are inserted into a document by a combination of an include instruction in the article file that specify the snippet to include and the source code file to take it from, and matching special comments in the source file that specify the beginning and end of the code sample. The syntax of the include instruction looks like this:

~~~
@@snippet(HelloWorld/HelloWorld.cpp, helloworld, cpp)
~~~

The first parameter specifies the file that contains the code snippet. The second parameter contains the name of the snippet as it is marked in the source file. Multiple snippets may be defined in a single source file, however each needs to have a unique name. The third parameter chooses a language for the generated Markdown code, the value has to be a name of a language supported by Pandoc (or whatever processes the Markdown file later). The snippet instructions have to be written in one separate line. This line will be replaced with the content of the snippet. Snippet instructions cannot be nested. The matching magic comments in the source file are written in the following format: 

~~~
//@@snippet_begin(helloworld)
using namespace std; 
cout << "Hello World!" << endl;
//@@snippet_end
~~~

The tool will look up the file, extract the snippet from it, and generate markdown output to render the code sample in the article. The code sample will include the lines between the delimiters, but not the delimiters themselves. It will also add the correct line numbers to the listing. 

## Generating the Markdown files

The SnippetExtractor filter needs to run on the Markdown input file that contains the include instruction, and will then generate a complete Markdown file from it. Usually this process is automated by `make` tools. A custom rule for the popular `latexmk` tool to process Latex documents would look something like this (remember to make sure snippetextractor is in the search path):

~~~
add_cus_dep('md.in', 'md', 0, 'mdin2md');
sub mdin2md {
    return system("snippetextractor '$_[0]'.md.in '$_[0]'.md");
}
~~~



