#Linux Cheat Sheet

##Installing Software
###<font color=#009154>aptitude</font>
   `Usage: aptitude [-S fname] [-u|-i]`<br>
   `       aptitude [options] <action> ...`<br>
   `  Actions (if none is specified, aptitude will enter interactive mode):`<br>
####Example<br>
`aptitude search rootname`, where everything in the debian package manager with *rootname* in its name will be displayed.
###<font color=#009154>apt-get</font>
`Usage: apt-get [options] command`<br>
`       apt-get [options] install|remove pkg1 [pkg2 ...]`<br>
`       apt-get [options] source pkg1 [pkg2 ...]`<br>
####Example<br>
`sudo apt-get install appname` will install *appname*.

##Searching for Text in Files
###<font color=#009154>grep</font>
`Usage: grep [OPTION]... PATTERN [FILE]...`<br>
`Search for PATTERN in each FILE or standard input.`<br>
`PATTERN is, by default, a basic regular expression (BRE).`<br>
####Examples [Adapted from here](http://www.thegeekstuff.com/2009/03/15-practical-unix-grep-command-examples/)<br>
* Search for **literal_string** in the **single file** filename<br>
 * `grep "literal_string" filename` <br>
* Search for **literal_string** in **multiple files** starting with "demo"<br>
 * `grep "literal_string" demo*`<br>
* Searching in all files **recursively** using grep -r<br>
 * `grep -r "literal_string" *`<br>
 * `grep -R "literal_string" *` _(also follows all symlinks)_<br>
* **Case insensitive** search using grep -i<br>
 * `grep -i "literal_string" filename`<br>
* Match **regular expression** regular_expression in file filename<br>
 * `grep "regular_expression" filename`<br>
* Checking for **full words, not for sub-strings** using grep -w<br>
 * `grep -iw "literal_string" filename`<br>
* Displaying lines **before/after/around the match** using grep -A, -B and -C<br>
`Context control:`<br>
`  -B, --before-context=NUM  print NUM lines of leading context`<br>
`  -A, --after-context=NUM   print NUM lines of trailing context`<br>
`  -C, --context=NUM         print NUM lines of output context`<br>
`  -NUM                      same as --context=NUM`<br>
`      --color[=WHEN],`<br>
`      --colour[=WHEN]       use markers to highlight the matching strings;`<br>
`                            WHEN is 'always', 'never', or 'auto'`<br>
 * `grep -A N "literal_string" filename`<br>
  prints the matched line, along with the **N lines after** it.<br>
 * `grep -B N "literal_string" filename`<br>
  prints the matched line, along with the **N lines before** it.<br>
 * `grep -C N "literal_string" filename`<br>
  prints the matched line, along with the **N lines before and after** it.<br> 
* **Invert match** using grep -v<br>
 * `grep -v "literal_string" filename`<br>
  prints all lines that **do not match** the search text.<br> 
* Display the lines which **do not match** the given **regular expressions**<br>
 * `grep -v -e "regular_expression1" -e "regular_expression2" filename`<br>
* Counting the **number of matching lines**<br>
 * `grep -c "literal_string" filename`<br>
* Counting the **number of non-matching lines**<br>
 * `grep -v -c "literal_string" filename`<br>
* Display **only the file names** that match the given pattern<br>
 * `grep -l "literal_string" *`<br>
* Show **only the matched string**<br>
 * `grep -o "regular_expression" filename`<br>
* Show the **position of the match** in the line<br>
 * `grep -o -b "regular_expression" filename`<br>
* Show **line number** while displaying the output<br>
 * `grep -n "literal_string" filename`<br>

##Searching for Files
###<font color=#009154>find</font>
`Usage: find [-H] [-L] [-P] [-Olevel] [-D help|tree|search|stat|rates|opt|exec] [path...] [expression]`<br>
`default path is the current directory; default expression is -print`<br>
`expression may consist of: operators, options, tests, and actions:`<br>
####Examples [Adapted from here](http://www.thegeekstuff.com/2009/03/15-practical-linux-find-command-examples/)<br>
* Find files **having a certain file name** filename<br>
 * `find -name "filename"`<br>
* Find files **having a certain file name** filename, **ignoring case**<br>
 * `find -iname "filename"`<br>
* Limit search to **specific directory level**<br>
 * `find / -name filename` _(finds all files named filename under the root directory)_<br>
 * `find / -mindepth 1 -maxdepth 3 -name filename` _(finds all files between 1 and 3 levels under the root directory)_<br>
* **Executing commands** on the files found by the find command<br>
 * `find -iname "filename" -exec md5sum {} \;` _(calculates the md5sum of all the files found)_<br>
* **Inverting the match**<br>
 * `find -maxdepth 1 -not -iname "filename"` _(shows all non-filename matches in the current directory)_<br>
* Finding files **based on their file permissions**<br>
 * `find . -perm -g=r -type f` _(shows all non-directory files with read permissions for the group)_<br>
 * `find . -perm -g=r` _(shows all files and directories with read permissions for the group)_<br>
* Find all **empty files** (zero byte files) in your home directory and its subdirectories<br>
 * `find ~ -empty`<br>
* Finding the **top 5 big files**<br>
 * `find . -type f -exec ls -s {} \; | sort -n -r | head -5`<br>
* Find files **based on file-type**<br>
 * `find . -type f` _(finds only normal files)_<br>
 * `find . -type f -name ".*"` _(finds hidden files)_<br> 
* Find files **by comparing with the modification time of another file**<br>
 * `find -newer filename` _(finds all files younger than the file filename)_<br>
* Find files by size<br>
 * `find ~ -size +100M` _(finds all files larger than 100MB)_<br>
 * `find ~ -size -100M` _(finds all files smaller than 100MB)_<br>
* Create alias for frequent find operations<br>
 * `alias rmao="find . -iname a.out -exec rm {} \;"` _(now, running `rmao` deletes all a.out files)_<br>
