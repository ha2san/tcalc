simple calculator that can be used in the terminal 

usage example:
```
$ tcalc "3*(2+1)"
9
```
```
$ tcalc
> 1.5*9.8+3.2
17.9
```
```
$ tcalc
> time
>(time mode) 25h67m24s
1 day 2 hours 7 minutes 24 seconds
1.08847 days or 26.1233 hours or 1567.4 minutes or 94044 seconds
>
```

```
$ tcalc
> $hello=23^2
529
> $hi=$hello*2
1058
> $hello=12
12
> variables
        hello => 12
        hi => 1058
```

operands: + - * ^ %

tested on a arch-based linux machine.

You must install editline but i will try to use something else in the near future...


(*src/hashmap.[ch] are not written by me* but I have the intention to implement
my own hashmap files that are shorter)
