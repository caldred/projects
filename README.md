# caldred's projects

## C++Projects

A collection of projects written in C++ for my computer science classes in undergrad. It includes implementations of Euchre and Blackjack (and simple AIs for both), a database, and solutions to the travelling salesman problem.

## MTGAutoencoder

The goal of this project is to build an autoencoder for Magic the Gathering decks. This would allow for the creation of embeddings both for decks as a whole, as well as embeddings for individual cards from the weight matrices of the first and last layers.

`Scraper.ipynb` scrapes all the decks from `MTGGoldfish.com` since the beginning of the Pioneer format (~1E4 decks or ~1E6 cards).

`Parser.ipynb` converts all those text decklists into n-hot encoded vectors (where n- is the number of times that card appears in that deck).

`Autoeconder.ipynb` implements a FNN in pytorch that attempts to recreate the original vectorized representation of the decklist after compressing it to a vector of length 32.

`ExploreEmbeddingSimilarity.ipynb` takes a look at the most similar cards to each card in both the encoder and decoder embedding space.

## PitchModels

The notebook has much more explanation, in general this offers a novel way of creating pitch models that only depend on "stuff" (inherent pitch characteristics) by finely clustering pitch types and using the clusters to generate expected probability distributions over usage by count and location.

## SwingPredictions

An example of how I attack a data science problem, in this case predicting whether or not the batter swung at a given pitch. Full description of my process is in the notebook. I don't have the full dataset available to publish, but I have included the head of both the train and test files.

## OlderProjects

These are older projects that still contain cool work, but may not be up to my current standard of work.

### CalRank

This is a general purpose ranking system, here applied to rank college football teams.

It is based off the principle that a team's true winning percentage, for a sufficiently connected graph of teams, can be thought of as their winning percentage, plus their opponent's winning percentage over expectation (.500), plus their opponent's opponent's winning percentage over expectation, etc. while excluding all games that involved the team in question from the calculations. This is improved by using an expected winning percentage rather than a binary result. This could be generated from a score differential or play-by-play data.

### MTG

This contains scripts related to the trading card game Magic: the Gathering.

`curve.py` calculates the optimal collection of mana costs and lands in a deck given the speed of a format, subject to some basic assumptions and constraints.

`mainstaples.py` reads in a collection of plaintext decklists and counts how often each card is found in the maindeck.

`scrape_mtg.py` scrapes the results of a magic tournament from the official magic website and calculates a result matrix by decktype.

### MarchMadness

This creates the optimal March Madness bracket to submit based on expected win probabilities, expected pick distributions, and the size of the pool being entered. Rather than relying on expensive monte-carlo simulations, which do not scale well with pool size, it uses several simplifying assumptions to generate a closed form solution.


### kde_xwoba
I turn the batted balls hit by a player into a probability distribution over exit parameters using kernel density estimation, and calculate expected results from a sample of that distribution.

### TruScore
This calculates the equivalent NFL score from a fantasy football matchup, based on the percentiles of scores in the specific league and the NFL. Offensive points increases your score while defensive points decrease your opponent'.
