# Fastscript

### By worldOneo

The name was the first best that came to my head.

Simple, turing complete language written in C++.

## I just wanted to make a language.

This is a basic implementation of a otf tokenizer and parser. It doesn't has a complex syntax. But to write a small script, the language is fine.

# Examples:

## Variable assignment:

```js
myint = 1;
mystring = "Hello";
mydouble = 2.56;
```

## Printing something:

```js
print("Hello, World!");
"This is a comment, you can use a string in empty space as comment.";
"Formated printing:";
printf("MyInt: {0}, MyString: {1}, MyDouble: {2}", myint, mystring, mydouble);
```

Output:

```nim
Hello, World!
MyInt: 1, MyString: Hello, MyDouble: 2.560000
```

## While

```js
"The While-Loop is the only loop we have";
index = 1;
while (index < 1024) {
  index = index * 2;
  printf("Index at {0}", index);
}
```

Output:

```nim
Index at 2
Index at 4
Index at 8
Index at 16
Index at 32
Index at 64
Index at 128
Index at 256
Index at 512
Index at 1024
```

## Input

```js
"We can read from stdin";
userInput = input("Enter your name: ");
printf("Hello, {0}!", userInput);
```

Example output:

```nim
Enter your name: worldOneo
Hello, worldOneo!
```

## Typing:

Variables are typed, but we can transform between different types:

```js
strNumber = input("Input a number: ");
intNumber = integer(strNumber);

if (intNumber < 5) {
  print("Your number is smaller than 5");
}
if (intNumber >= 5) {
  print("Your number is greater or equals to 5!");
}
```

Example output:

```nim
Input a number: 5
Your number is greater or equals to 5!

#(second run)
Input a number: 4
Your number is smaller than 5
```

## If

As seen above we have if-statements.  
No elses, only ifs.

## Functions

```js
"functions can be defined like this:";
identifier:(arg1, arg2) {
  printf("{0} {1}", arg1, arg2);
}
"They can be called like builtin-functions";
identifier("Hello, ", "World!");
```

Output:

```nim
Hello, World!
```

### Scopes

Functions define variables in a own scope which gets deleted when the function reaches the end.
To force a variable in local scope use `=#` instead of `=`, and to force it in to global scope use `=$`.
The default scope is:
if a variable exists in global context that is used, else the local scope is used.
Example:

```js
_WRE_1 = 1;
localscope: () {
    _WRE_1 =# 2;
}
noscope: () {
    _WRE_1 = 2;
}
globalscope: () {
    "this function creates a new global vriable";
    _WRE_2 =$ 3;
}
localscope();
printf("WRE: {0}", _WRE_1);
noscope();
printf("WRE: {0}", _WRE_1);
globalscope();
printf("WRE: {0}", _WRE_2);
```
output:

```nim
WRE: 1
WRE: 2
WRE: 3
```

## The language has of course every bitwise operators

## [Example script using every feature](https://github.com/worldOneo/fastscript/blob/master/script.fsc)