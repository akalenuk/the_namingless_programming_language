# The namingless programming language

Naming is hard. Let's see how far can we go without.


## What's this?

This is a programming language based on three paradigms:

- [Tacit programming](https://en.wikipedia.org/wiki/Tacit_programming)
- [Stack-oriented programming](https://en.wikipedia.org/wiki/Stack-oriented_programming)
- [Array programming](https://en.wikipedia.org/wiki/Array_programming)

The main feature of the language is its avoidance of any naming of any sort. True to this maxima, the language itself doesn't have a name. "The namingless programming language" is a definition. 

Since there is only one such language in existence, *it doesn't need a name*.


## What it's for?

Fun. Mostly fun. This is a language for recreational programming.

Well, of course, you can also use it as a teaching tool to showcase tacit, stack-oriented, or array programming. Or use it for punishment in a BDSM play. I don't judge.


## How does the code in this language look like?

Like this:

    i_^_b_H_i_cpp^_)_V_b_v_J_^_E_H_leafL_==^_)_V_H_Z_Z_^_)_V_H_I_^_E_1^_2^_#_G_Z_Z_^_E_1^_2^_#_H_$_L_-^_G_m_G_&_&_


## Holy shit!

Yes.

Sorry.


## What are the main concepts?

### Data structures

There is one and only one data structure. Since there is only one, *it doesn't need a name*.

So the data structure is a tree of chars. Every node is either a leaf containing a char, or a branch containing a dynamic array of the data structures. The array may also be empty. An empty branch is still a branch.

A string is a branch where every subbranch is a leaf.

A number is a string. Yes. The language supports decimal arithmetics on strings. Go COBOL!

An array is a branch where every subbranch is a string.

A matrix is a branch where every subbranch is an array.

Please note that none of these terms are names for anything language-specific. They are widely known data structures that are implementable in the language's data structure.

### Operations

There is also the operation. Not "an operation" but "the operation" since there is only one operation in the language. Since there is only one, *it doesn't need a name* either.

The operation is spelled '_' and it takes the last element from the branch before it and acts accordingly. So essentially the semantics of the operation is set by the pair of a prefix - a symbol before the operation - and the operation itself.

E. g. to add 2 and 2, you need to:

1. put a char 2 as a string. The pair for that is "^" and "_".

    2^_

2. then you need another 2 as a string. You can do the same "2^_" thing but you can also duplicate the last element in the current branch with a "H" and "_" pair.

    H^_

3. finally, you need to perform the addition itself. That's easy, that's "+" and "_".

    +_

So the final program will look like this:

    2^_H_+_

And when run, it will result in:

    4

### Ok but the program you write in the namingless language should have a name right?

To avoid the naming problem for the programs you write, the language uses the name of the executable as the source code.

Let that sink in.

You get the executable interpreter for the language and rename it with the valid code in the language. This way, the file you run doesn't have a name per se but the program itself is the name of the executable you run.

So to run the scary program from above you do this:

	./build.sh
	mv the_namingless_programming_language i_^_b_H_i_cpp^_)_V_b_v_J_^_E_H_leafL_==^_)_V_H_Z_Z_^_)_V_H_I_^_E_1^_2^_#_G_Z_Z_^_E_1^_2^_#_H_$_L_-^_G_m_G_&_&_
	./i_^_b_H_i_cpp^_)_V_b_v_J_^_E_H_leafL_==^_)_V_H_Z_Z_^_)_V_H_I_^_E_1^_2^_#_G_Z_Z_^_E_1^_2^_#_H_$_L_-^_G_m_G_&_&_

Of course, you can just copy and tweak the program you already have. In fact, that's what we normally do with Python, shell, or Perl scripts anyway.

### What operation pairs are available?

Here is the full list of the operation pair prefixes.

- . - exit
- U - underscore
- Z - slash
- N - backslash
- J - line break
- i - dot
- L - space
- I - single quote
- Y - double quote
- ^ - elevate all the last elements of the same rank
- | - put an element of the current branch on top by index
- \# - remove all but the targeted by index element for the selected depth
- m - replicate an item multiple times
- H - duplicate the last element
- X - drop the last element
- G - swap the last two elements
- A - elevate an empty element
- $ - count
- v - deelevate last element
- \+ - addition
- \- - subtraction
- x - multiplication
- z - division
- = - equal?
- % - numerically equal?
- < - less?
- \> - greater?
- ( - substring?
- ) - superstring?
- \[ - string starts with?
- \] - string ends with?
- T - Boolean not
- W - Boolean and
- M - Boolean or
- C - interpret as number if possible, 0 otherwise
- & - concatenate strings
- E - split a string
- D - join strings
- V - filter by a logical value
- b - load from file
- p - save to file
- o - delete file
- e - help

By the way, the list is automatically generated from the source code by the "i_^_b_H_i_cpp^_)_V_b_v_J_^_E_H_leafL_==^_)_V_H_Z_Z_^_)_V_H_I_^_E_1^_2^_#_G_Z_Z_^_E_1^_2^_#_H_$_L_-^_G_m_G_&_&_".


### The most important operation pair

#### Exit

Since the source code for the language comes from the name of the executable, and on Windows, a dot separates the file name from its extension, the dot was chosen as a prefix that stops the execution. You can also use it to separate code from comments like this:

    i_^_b_H_i_cpp^_)_V_b_v_J_^_E_H_leafL_==^_)_V_H_Z_Z_^_)_V_H_I_^_E_1^_2^_#_G_Z_Z_^_E_1^_2^_#_H_$_L_-^_G_m_G_&_&_._list of operation prefixes


### Escape sequences

#### Underscore

Since '_' is the command, you can't use it in arbitrary strings as it is. So the escape for the underscore is "U_". 

"U" has been chosen since it kind of contains the underscore in its bottom part. This is the recurring pattern. A grapheme that substitutes a symbol is usually a symbol with something else.


#### Slash

You can't usually use slashes in the file names. And even when you can it wouldn't be a good idea. Trust me. So there is an escape pair that puts "/" into the current data structure, and it is "Z_".

Like with "U", "Z" is a slash plus two extra lines.


#### Backslash

By the same logic, the backslash is a "N_" pair. "\" plus two extra lines.


#### Line break

"J" looks like a bit like a return sign "⏎". So the pair for the line break is "J_".


#### Dot

Since a dot is used as a name-extension separator on Windows, we can use "i_" as a dot substitute just not to mess with the way file managers prefer to show stuff.


#### Space

Although there is nothing wrong with putting space in the file name, sometimes it makes routine UI operations like copying things harder so we can avoid spaces by "L_" substitution.

"L" is a horizontal line representing the space itself, and a vertical line that serves no purpose.


#### Single quote

"I_" stands for the single quote. You probably wouldn't get it until you see the double-quote pair.


#### Double quote

"Y_" is the double quote. "I" and "Y", single and double. Does it make sense now?


### Data handling

#### Elevate all the last elements of the same rank

I see your confusion. This prefix doesn't have a coherent name. Well, naming *is* hard, that's why I started the whole thing to begin with. 

What it does *usually* is it turns a piece of string into a subbranch conining the piece of string.

E. g. you want to add 12 and 23 together. In a normal language, you have literals, syntaxis, and operators, so `12 + 23` is the common way to do that. In this language, you only have a string of chars as input, so to add two numbers together, you need to segregate one from another first.

When you enter `12`, you only enter char `1` followed by char `2`. Your current branch contains two leaf elements.

    leaf(1) leaf(2)

Now you elevate all the elements of the same rank making these two into a subbranch with two leaves inside.

    12^_

...results in...

    branch(leaf(1) leaf(2))

Now you add two more chars:

    12^_34

    branch(leaf(1) leaf(2)) leaf(3) leaf(4)

And then you elevate the last elements until they are of the same rank resulting in this:

    12^_34^_

    branch(leaf(1) leaf(2)) branch(leaf(3) leaf(4))

And only now, when you have two branches with what are essentially strings inside, you can use another operation pair to add them up.

    12^_34^_+_

This now results in a new branch containing the following:

    branch(leaf(4) leaf(6))

This outputs to a tab and `46`. You can deelevate it back with the `v_` pair, and then you'll get `46` without any tabs, but that's a completely different story.


#### Put an element of the current branch on top by index

This is something like `[]` in normal languages. A way to access an array.

Let's say our branch is filled like this:

    leaf(1) leaf(2) leaf(4) leaf(8)

Since we might even know how many leaves there are, we start counting indices from the end. And for... reasons, we also start from 0.

So doing `2^_|_` to our subbranch picks the *third* element from the right, and copies it to the rightmost position in the branch.

    leaf(1) leaf(2) leaf(4) leaf(8) leaf(2)


#### Remove all but the targeted by index element for the selected depth

This is a way to access all the elements in a matrix, or a tensor, or a tree that lies on a certain depth, and in a certain position too.

Take this program for example:

    1^_2^_3^_^_4^_5^_6^_^_^_2^_2^_#_

First, we elevate 3 chars so they become strings (or in terms of the language, branches that only contain leaves).

    branch(leaf(1)) branch(leaf(2)) branch(leaf(3))

Then we elevate the strings, yes, all three of them, so they now constitute an array of strings (or, in terms of the language again, a branch where all the branches are the branches that only contain leaves).

    branch(branch(leaf(1)) branch(leaf(2)) branch(leaf(3)))

Then we add three more strings and elevate them as well.

    branch(branch(leaf(1)) branch(leaf(2)) branch(leaf(3))) branch(branch(leaf(4)) branch(leaf(5)) branch(leaf(6)))

Then we evaluate the two branches making a matrix of strings (or in terms of the language, oh boy, a branch that contains several branches with an equal number of branches that only contain leaves each).

    branch(branch(branch(leaf(1)) branch(leaf(2)) branch(leaf(3))) branch(branch(leaf(4)) branch(leaf(5)) branch(leaf(6))))

Or in more conventional notation:

    1 2 3
    4 5 6

Now we do this:

2^_2^_#_

The first `2` is the index. And it also enumerates elements starting from 0, so `2` actually means "the third".

The second `2` is the depth. Also starting from 0. `2` and `2` means that we want the third element from the branch on the third level of embededness. That's `leaf(3)` and `leaf(6)` but also packed in a branch so it's more like `branch(leaf(3) leaf(6))`.

This operation prefix may also pick from the 0-th deepness level so, for instance, this program:

    1^_2^_3^_2^_0^_#_

Results in `3`.


#### Replicate an item multiple times

Well, that's easy. If there is an element in the current branch, it can be multiplicated. For example, `3` times by doing `3^_m_`:

    test^_3^_m_

results in:

    test
    test
    test


#### Duplicate the last element

This is the abbreviated version of replication. It always adds exactly 1 copy of the last element.

    test^_H_

results in:

    test
    test


#### Drop the last element

The last element can also be easily removed.

    1^_2^_3^_X_

results in:

    1
    2


#### Swap the last two elements

Or swapped with the previous element.

    1^_2^_3^_G_

results in:

    1
    3
    2


#### Elevate an empty element

Sometimes you need an empty string, an empty array, or an empty matrix. You can't elevate an empty element with `^_` because it elevates all the consequent elements of the same rank starting from the last one. So there is a dedicated prefix that elevates an empty element out of the blue.

    A_

results in

    branch()


#### Count

This simply returns the amount of subbranches in the last element of the current branch.

    1^_2^_3^_^_$_

results in:

    3


#### Deelevate the last element

Just like several subbranches can be elevated into one branch containing them all, the last element in the branch can be deelevated, putting all its contents in the current branch.

    1^_2^_3^_^_v_

results, unsurprisingly, in:

    1
    2
    3

The symbol pairs the grapheme for the "elevate" by the way. Isn't that sweet?


### Arithmetics

I love floating-point numbers. I wrote several tutorials on them:

-[Yet another floating-point tutorial](https://wordsandbuttons.online/yet_another_floating_point_tutorial.html)

-[Estimating floating-point error the easy way](https://wordsandbuttons.online/estimating_floating_point_error_th-e_easy_way.html)

-[Why is it ok to divide by 0.0? ](https://wordsandbuttons.online/why_is_it_ok_to_divide_by_0_0.html)

I even wrote a whole book on [Geometry for Programmers](https://www.amazon.com/Geometry-Programmers-Oleksandr-Kaleniuk/dp/1633439607) and it's half symbolic computations, half numeric so at least half of the book is concerned with floating-point numbers too.

But for this particular language, I wanted to avoid introducing another type so much, that I do all the arithmetics on decimal strings. Like in COBOL.

There is one unorthodox rule: the precision of the result is the maximum precision of the argument. The rule means that `1/3` and `1.00/3` result in different numbers. The former is `0`, and the latter - `0.33`. The rest is business as usual.

Except, of course, this time the expressions are in postfix notation, they propagate to tensors, and instead of operators we have prefix+operation pairs.


#### Addition

The prefix for addition is `+`.

    2^_2^_+_

    4

In case you're wondering what the "they propagate to tensors" statement from above means, that means that you can add a number to an array:

    1^_2^_^_3^_+_

    4
    5

Or add elements in a pair of arrays together:

    1^_2^_^_3^_4^_^_+_

    4
    6

You can also add matrices or even arbitrary trees as long as they are of equal rank, size, and configuration. All with a single operation. You don't need `for`s in this language.


#### Subtraction

The prefix for subtraction is `-`.

    4^_2^_-_

    2


#### Multiplication

Since we wouldn't use `*` for multiplication, remember, that the source code comes from the file name, the prefix for the multiplication would be `x`.

    2^_2^_x_

    4


#### Division

Just like that, we wouldn't use `/` for division either. The prefix for the division is `z`.

    4^_2^_z_

    4


### Logic

Logical operations in this language work pretty much like arithmetics. They work on strings and propagate to tensors and trees. It's just the result of a comparison cast on a pair of trees is a tree of `0` and `1`s.


#### Equal?

This compares two strings. Strings may or may not be numbers.

    2^_2^_=_

    1


#### Numerically equal?

This compares two strings. Strings are expected to be numbers but they may have trailing zeroes.

    2^_2.00^_=_

    1


#### Less?

Expects numbers. Returns `1` if the former is less than the latter. `0` otherwise:

    2^_3^_<_

    1


#### Greater?

Also expects numbers. Returns `1` if the former is greater than the latter. `0` otherwise:

    3^_2^_>_

    1


#### Substring?

Expects strings. Returns `1` if the former is a substring of the latter. `0` otherwise:

    bob^_notabobbutcontainsone^_(_

    1


#### Superstring?

Symmetrical to the "substring?" operation pair. Returns `1` if the former is a superstring of the latter. `0` otherwise:

    notabobbutcontainsone^_bob^_)_

    1


#### String starts with?

Expects strings. Returns `1` if the latter is what a former starts with. `0` otherwise:

    bobbutcontainsone^_bob^_\[_

    1


#### String ends with?

Expects strings. Returns `1` if the latter is what a former finishes with. `0` otherwise:

    notabob^_bob^_\]_

    1


#### Boolean not

Expects a string of `0` and `1` only. Inverts the values in a tree.

    1^_T_

    0


#### Boolean and

Also expects strings of `0` and `1` only. Does the Boolean "and".

    1^_1^_W_

    1


#### Boolean or

You guessed it, also expects strings of `0` and `1` only. Does the Boolean "or".

    0^_1^_M_

    1


### Strings


#### Interpret as a number if possible, 0 otherwise

In this language, numbers are strings that can be interpreted as numbers. So ten digits, one optional dot, and an optional minus sign. Some strings are obviously not numbers but we might wish they were. For this scenario, a special prefix exists and it's `C`. It turns all the non-numbers into `0`,

    123^_not123^_^_C_

    123
    0


#### Concatenate strings

Very simple operation that glues two strings together.

    2^_2^_&_

    22


#### Split a string

Splits a string by a delimiter (also a string).

    pre,the,post^_,^_E_

    pre
    the
    post


#### Join strings

Joins string back into a single string with a delimiter.

    pre^_the^_post^_^_-^D_

    pre-the-post


#### Replace

Got you! There is no "replace a string with a string" operation pair in the language. To do the replace, you do a split-then-join idiom.

    pre,the,post^_,^_E_-^_D_

    pre-the-post

One symbol spared for something else.


### Filter

There is only one filter operation so far, and it is:


#### Filter by a logical value

It expects two trees of the same configuration. One with strings the other with, well, also strings but only `1`s and `0`s. The filter goes through the first tree and removes every element that is not `1` in the corresponding tree.

    pre,the,post^_,^_E_H_p^_)_V_

So this program

1. elevates a string "pre,the,post",
2. splits it by the `,` getting an array `put the post`,
3. duplicates the split string `put the post`,
4. applies the "is a superstring of `p`" for the last split tree resulting in array `1 0 1`.
5. and, finally, applies the filter `1 0 1` to the `put the post` array resulting in a smaller array with strings where the letter `p` occurs:

    pre
    post


### Files

In this language, a grapheme for a file is a small circle `o`. There are exactly 3 operation prefixes that work with files, all of them have a small circle in them.


#### Load from file

The grapheme is `b` so it's like a file goes up from slow persistent memory to the fast operational.

    somefilei_txt^_b_

results in... whatever there is in the `somefile.txt`. The result will be delivered as a string - a branch where every subbranch is a leaf containing a character value.

Also, this operation pair doubles as a 'list directory' command. If the argument for the `b_` is a directory name, then the result will be not a string but a list of strings each containing a file or a directory name.


#### Save to file

The grapheme is inverse to the one for the "load from file" it's `p`. So a file going down closer to earth.

    somethingL_toL_putL_inL_aL_file^_somefilei_txt^_p_

results in a string "something to put in a file" being put in a file "somefile.txt"


#### Delete a file

The grapheme now is just a circle `o`. Well, it might not make too much sense but it shows that the operation is a pure side effect with no effect on the current branch. Well, except for the file name being consumed.

    somefilei_txt^_o_

deletes the "somefile.txt" file if there is one.


### Help

Last but not least, the grapheme for the help message explaining what the hell this thing does is `e`. The reasoning for this choice is simple. When you build the thing, the resulting file name is `the_namingless_programming_language`. So when you run it as it is, the first operation pair the interpreter meets is `e_` from `the_...`.


### Ok, I get it now. I love it! But there is not much the interpreter can do at the moment. Can I contribute?

Sure! To add an operation pair to the language you might want to do three things.

1. Invent a meaningful program that wouldn't run unless you add your thing. 
2. Add your thing so the program will run and be meaningful.
3. Prepare the pull request with the changes in the code and a program added to the list of meaningful programs.

I'll start.


### The list of meaningful programs

#### i_^_b_H_i_cpp^_)_V_b_v_J_^_E_H_leafL_==^_)_V_H_Z_Z_^_)_V_H_I_^_E_1^_2^_#_G_Z_Z_^_E_1^_2^_#_H_$_L_-^_G_m_G_&_&_

This program parses the `.cpp` files in the current directory looking for a string like this:

    } else if(right.branches.back().leaf == 'e') { // help

Such strings are then processed to extract the operation prefix, `e` in the example, and the comment, ` help` in the example.

The prefixes and comments are then glued together with a dash ` -`.

The resulting array is the list of operation prefixes this language supports with brief explanations of them taken from the comments:

                . - exit
                U - underscore
                Z - slash
                N - backslash
                J - line break
                i - dot
                L - space
                I - single quote
                Y - double quote
                ^ - elevate all the last elements of the same rank
                | - put an element of the current branch on top by index
                \# - remove all but the targeted by index element for the selected depth
                m - replicate an item multiple times
                H - duplicate the last element
                X - drop the last element
                G - swap the last two elements
                A - elevate an empty element
                $ - count
                v - deelevate last element
                \+ - addition
                \- - subtraction
                x - multiplication
                z - division
                = - equal?
                % - numerically equal?
                < - less?
                \> - greater?
                ( - substring?
                ) - superstring?
                \[ - string starts with?
                \] - string ends with?
                T - Boolean not
                W - Boolean and
                M - Boolean or
                C - interpret as number if possible, 0 otherwise
                & - concatenate strings
                E - split a string
                D - join strings
                V - filter by a logical value
                b - load from file
                p - save to file
                o - delete file
                e - help
