cgrep.c is a command line tool built to imitate grep without regular expression capability. Behavior can be modified with the use of the following
flags/options:

-i: Ignore case <br/>
-n: Print line numbers <br/> 
-h: Help <br/>

Compile:
```
$ gcc -o cgrep cgrep.c
```

Execute:
```
$ ./cgrep [OPTION]... FILE
```

## Authors

* **Thomas McDowell**
