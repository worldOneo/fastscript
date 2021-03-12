# Fastscript

### By worldOneo

The name was the first best that came to my head.

Simple, turing complete language written in C++.

## I just wanted to make a language.

This is a basic implementation of a otf tokenizer and parser. It doesn't get has very complex syntax, it doesn't even has functions. But to write a small script, the language is fine.

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

## The language has of course every bitwise operators

## [Example script using every feature](https://github.com/worldOneo/fastscript/blob/master/script.fsc)