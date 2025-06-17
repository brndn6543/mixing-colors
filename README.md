# Color Mixing Using RGB LED
This demonstrates how to mix various colors using an RGB LED. It takes user input
for the standard colors, but also allows the user to select `magenta`, `cyan`, `orange`, `white`, and `yellow`.

## Code
The code is similar to my previous sketch with updated support for color mixing in the `map`.
```c++
std::map<String, std::tuple<int, int, int>> colorMap = {
	{"red", {255, 0, 0}},
	{"green", {0, 255, 0}},
	{"blue", {0, 0, 255}},
	{"cyan", {0, 255, 255}},
	{"magenta", {255, 0, 255}},
	{"white", {255, 255, 255}},
	{"orange", {255, 165, 0}},
	{"yellow", {255, 255, 0}}
};
```

There is an additional function `setColor`  that adjust the RGB LED colors based on a provided tuple.
```c++
void setColor(int r, int g, int b, int brightness)
```
**Parameters**


- `r, g, b`: The color intensities for red, green and blue channels. Values range from `0` to `255`.
- `brightness`: Desired brightness level on a scale from `1` to `10`.

```c++
int pwmRed = map(r * brightness, 0, 2550, 0, 255);
int pwmGreen = map(g * brightness, 0, 2550, 0, 255);
int pwmBlue = map(b * brightness, 0, 2550, 0, 255);
```

- The function first scales the RGB intensities according to the brightness.
- Since brightness ranges from `1-10`, multiplying by brightness gives a range of `0-255`.
- `map()` proportionally scales this `0-2550` range down to `0-255`.

The scaled RGB values are then sent as PWM signals to the Arduino pins controlling the RGB LED.

## Wiring
[![rgb-led-2.png](https://i.postimg.cc/K88Q9rvM/rgb-led-2.png)](https://postimg.cc/YhT10FFr)