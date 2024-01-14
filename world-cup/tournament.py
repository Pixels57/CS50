# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 10


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    with open(sys.argv[1]) as file:
        file_reader = csv.DictReader(file)
        for wcteams in file_reader:
            teams.append(wcteams)

        for i in teams:
            i["rating"] = int(i["rating"])
    # TODO: Read teams into memory from file

    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    t = simulate_tournament(teams)
    teamname = t
    counts[teamname] = 1
    for i in range(N):
        team = simulate_tournament(teams)
        if counts.get(teamname):
            counts[teamname] = 1
        else:
            c = counts.get(teamname)
            c += 1
            newc = {teamname : c}
            counts.update(newc)
    # Print each team's chances of winning, according to simulation
    # for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[teamname] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    if len(teams) == 2:
        if simulate_game(teams[0], teams[1]):
            return teams[0]["team"]
        else:
            return teams[1]["team"]

    if len(teams) == 4:
        winers4 = simulate_round(teams).copy()
        if simulate_game(winers4[0], winers4[1]):
            return winers4[0]["team"]
        else:
            return winers4[1]["team"]

    if len(teams) == 8:
        winers8 = simulate_round(teams).copy()
        winers4 = simulate_round(winers8).copy()
        if simulate_game(winers4[0], winers4[1]):
            return winers4[0]["team"]
        else:
            return winers4[1]["team"]

    if len(teams) == 16:
        winers16 = simulate_round(teams).copy()
        winers8 = simulate_round(winers16).copy()
        winers4 = simulate_round(winers8).copy()
        if simulate_game(winers4[0], winers4[1]):
            return winers4[0]["team"]
        else:
            return winers4[1]["team"]

    ##winers = []
    ##for teamm in teams:
    ## winers.append[teamm]
    ##length = len(teams)
   ## winers_quarter = simulate_round(teams).copy()
    ##winers_semi = simulate_round(winers_quarter).copy()
   ## winers_final = simulate_round(winers_semi).copy()
    ##length = len(winers)
    ##if simulate_game(winers_final[0], winers_final[1]):
     ##   return winers_final[0]
   ## else:
    ##    return winers_final[1]


if __name__ == "__main__":
    main()
