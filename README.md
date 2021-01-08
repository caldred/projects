# caldred's projects

This is a collection of small personal projects written in python over the past several years. Most relate to sports analytics or trading card games.

## CalRank

This is a general purpose ranking system, here applied to rank college football teams.

It is based off the principle that a team's true winning percentage, for a sufficiently connected graph of teams, can be thought of as their winning percentage, plus their opponent's winning percentage over expectation (.500), plus their opponent's opponent's winning percentage over expectation, etc. while excluding all games that involved the team in question from the calculations. This is improved by using an expected winning percentage rather than a binary result. This could be generated from a score differential or play-by-play data.

## MTG

This contains scripts related to the trading card game Magic: the Gathering.

`curve.py` calculates the optimal collection of mana costs and lands in a deck given the speed of a format, subject to some basic assumptions and constraints.

`mainstaples.py` reads in a collection of plaintext decklists and counts how often each card is found in the maindeck.

`scrape_mtg.py` scrapes the results of a magic tournament from the official magic website and calculates a result matrix by decktype.

## MarchMadness

This creates the optimal March Madness bracket to submit based on expected win probabilities, expected pick distributions, and the size of the pool being entered. Rather than relying on expensive monte-carlo simulations, which do not scale well with pool size, it uses several simplifying assumptions to generate a closed form solution.

## PitchModels
The notebook has much more explanation, in general this offers a novel way of creating pitch models that only depend on "stuff" (inherent pitch characteristics) by finely clustering pitch types and using the clusters to generate expected probability distributions over usage by count and location.

## SwingPredictions
An example of how I attack a data science problem, in this case predicting whether or not the batter swung at a given pitch. Full description of my process is in the notebook. I don't have the full dataset available to publish, but I have included the head of both the train and test files.

## kde_xwoba
I turn the batted balls hit by a player into a probability distribution over exit parameters using kernel density estimation, and calculate expected results from a sample of that distribution.
