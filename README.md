# Simple and minimal wrapper over ncurses and winAPI
> ## WIP

###Examples:

<h5>print strings to term</h5>
```cpp
screen_setup();
const char* c_string = "c string";
std::string cpp_string = "c++ string";

print(1, 1, c_string);
print(1, 2, cpp_string.c_str());

getch();
close_window();
```

<h5>print colored strings to term</h5>
```cpp
...

Color color = Color();
change_color(color.red);
print(1,1, "red");

change_color(color.magenta);
print(1,2, "magenta");

change_color(color.green);
print(1,3, "green");

change_color(color.blue);
print(1,4, "blue");

change_color(color.yellow);
print(1,5,"yellow");

change_color(color.black);
print(1,6,"black");

change_color(color.white);
print(1,7,"white");

...
```
