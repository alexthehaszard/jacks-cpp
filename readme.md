# jacks (in C++!)

I previously wrote a simulator for this game in Javascript. That one has a nice UI and you can actually play it!

When I wrote that one, the goal was always to simulate as many runs as possible so that I could determine an estimate for the win rate you'd get playing it. It's trivial to understand that the game is deterministic (once the cards are shuffled).

It originally took HOURS to simulate 100,000 games. That was the goal.

Now, with this version, in some slightly better optimized c++, I was able to run 100,000 games (on the same hardware) in only ~300ms. A _slight_ improvement.

### Results

#### 100,000 games

10,919/100,000 (10.919%, 348ms)

#### 10,000,000 games

1,088,974/10,000,000 (10.88974%, 35104ms)

### Further improvements

- Better testing... I am not 100% sure we are simulating the game correctly every time. Hopefully we are.
- Running it through a profiler, to see where speedups can be made
