# differentiator
- 📏 Finally, the days when the Department of Higher Mathematics was forced to calculate derivatives have passed. Now it is time for my differentiator
<p align="center">
  <img width="600" height="800" src="https://github.com/MaxGroshev/differentiator/blob/master/readme_pic/Screenshot%20from%202023-04-25%2015-15-09.png">
</p>

# Do you want the same way?
```
> git clone https://github.com/MaxGroshev/differentiator.git
> mkdir obj
```
---

#### Required programs
- LaTeX-full (if want get result in LaTeX format)
- graphviz

---
# How to use
```
> cd test_files
> nano (or any other text editor) read_descent.txt
> input your func (without any extra symbols)
> cd ..
> make
> ./differ
> make latex_t (to get your result in beatiful LaTeX format)
```
# What it can?
- to differentiate functions such as:
  * `const`
  * `U+V`
  * `U*V`
  * `U/V`
  * `U(V)`
  * `sinx`
  * `cosx`
  * `tgx`
  * `ctgx`
  * `lnx`
  * `f(x)^g(x)`
- search partial derivatives
  * `df/dx`
  * `df/dy`
  * `etc`
- to simplify the result
- to build graphics in python style (if you have Matplotlib)
<p align="center">
  <img width="460" height="300" src="https://github.com/MaxGroshev/differentiator/blob/master/readme_pic/Screenshot%20from%202023-04-25%2015-14-32.png">
</p>


---
# Why I should choose this differentiator
- low memory consuption
- full control of every stage of work (includeing HTML logs + graphics dump)
- include library for work with graphviz
- include DSL for comfortable work and easy expantions of abilities


<h4 align="center">Each stage</h4>
<p align="center">
  <img width="700" height="300" src="https://github.com/MaxGroshev/differentiator/blob/master/readme_pic/Screenshot%20from%202023-04-23%2000-07-01.png">
</p>

