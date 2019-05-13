/*
You've sneaked into another supply closet - this time, it's across from the prototype suit manufacturing lab. You need to sneak inside and fix the issues with the suit, but there's a guard stationed outside the lab, so this is as close as you can safely get.

As you search the closet for anything that might help, you discover that you're not the first person to want to sneak in. Covering the walls, someone has spent an hour starting every midnight for the past few months secretly observing this guard post! They've been writing down the ID of the one guard on duty that night - the Elves seem to have decided that one guard was enough for the overnight shift - as well as when they fall asleep or wake up while at their post (your puzzle input).

For example, consider the following records, which have already been organized into chronological order:

[1518-11-01 00:00] Guard #10 begins shift
[1518-11-01 00:05] falls asleep
[1518-11-01 00:25] wakes up
[1518-11-01 00:30] falls asleep
[1518-11-01 00:55] wakes up
[1518-11-01 23:58] Guard #99 begins shift
[1518-11-02 00:40] falls asleep
[1518-11-02 00:50] wakes up
[1518-11-03 00:05] Guard #10 begins shift
[1518-11-03 00:24] falls asleep
[1518-11-03 00:29] wakes up
[1518-11-04 00:02] Guard #99 begins shift
[1518-11-04 00:36] falls asleep
[1518-11-04 00:46] wakes up
[1518-11-05 00:03] Guard #99 begins shift
[1518-11-05 00:45] falls asleep
[1518-11-05 00:55] wakes up
Timestamps are written using year-month-day hour:minute format. The guard falling asleep or waking up is always the one whose shift most recently started. Because all asleep/awake times are during the midnight hour (00:00 - 00:59), only the minute portion (00 - 59) is relevant for those events.

Visually, these records show that the guards are asleep at these times:

Date   ID   Minute
			000000000011111111112222222222333333333344444444445555555555
			012345678901234567890123456789012345678901234567890123456789
11-01  #10  .....####################.....#########################.....
11-02  #99  ........................................##########..........
11-03  #10  ........................#####...............................
11-04  #99  ....................................##########..............
11-05  #99  .............................................##########.....
The columns are Date, which shows the month-day portion of the relevant day; ID, which shows the guard on duty that day; and Minute, which shows the minutes during which the guard was asleep within the midnight hour. (The Minute column's header shows the minute's ten's digit in the first row and the one's digit in the second row.) Awake is shown as ., and asleep is shown as #.

Note that guards count as asleep on the minute they fall asleep, and they count as awake on the minute they wake up. For example, because Guard #10 wakes up at 00:25 on 1518-11-01, minute 25 is marked as awake.

If you can figure out the guard most likely to be asleep at a specific time, you might be able to trick that guard into working tonight so you can have the best chance of sneaking in. You have two strategies for choosing the best guard/minute combination.

Strategy 1: Find the guard that has the most minutes asleep. What minute does that guard spend asleep the most?

In the example above, Guard #10 spent the most minutes asleep, a total of 50 minutes (20+25+5), while Guard #99 only slept for a total of 30 minutes (10+10+10). Guard #10 was asleep most during minute 24 (on two days, whereas any other minute the guard was asleep was only seen on one day).

While this example listed the entries in chronological order, your entries are in the order you found them. You'll need to organize them before they can be analyzed.

What is the ID of the guard you chose multiplied by the minute you chose? (In the above example, the answer would be 10 * 24 = 240.)

To begin, get your puzzle input.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int main()
{
	std::fstream file("input.txt");
	std::string line;
	std::vector<std::string> lines;
	// Read file
	while (file.is_open() && std::getline(file, line))
	{
		lines.push_back(line);
	}
	// Sort file in memory, abuse ASCII string sorting
	std::sort(lines.begin(), lines.end());

	int currentGuard = 0;
	// Gaurd[min] = number of times the guard slept that minute
	std::map<int, std::map<int, int>> guardSleepMinutes;
	int sleepStart = 0;

	// Parse all events
	for (std::string line : lines)
	{
		int timestamp = std::stoi(line.substr(15, 2));
		if (line.find("Guard") != std::string::npos)
		{
			currentGuard = std::stoi(line.substr(line.find("#") + 1, 4));
			if(guardSleepMinutes.find(currentGuard) == guardSleepMinutes.end())
				guardSleepMinutes[currentGuard] = std::map<int, int>();
		}
		else if (line.find("falls") != std::string::npos)
		{
			sleepStart = timestamp;
		}
		else if (line.find("wakes") != std::string::npos)
		{
			for (int i = sleepStart; i <= timestamp; i++) 
			{
				guardSleepMinutes[currentGuard][i]++;
			}
		}
	}

	// Calculate 'best' guard
	int mostMinutesAsleep = 0, bestGuard = 0, bestMinute = 0;
	for (auto i : guardSleepMinutes)
	{
		int guard = i.first;
		int totalMinutesAsleep = 0;
		int minuteMostSlept = 0;
		int highestNumberOfMinutesSlept = 0;
		for (auto j : i.second)
		{
			int minute = j.first;
			int numberOfTimesAsleep = j.second;
			if (numberOfTimesAsleep > highestNumberOfMinutesSlept)
			{
				highestNumberOfMinutesSlept = numberOfTimesAsleep;
				minuteMostSlept = minute;
			}
			totalMinutesAsleep += numberOfTimesAsleep;
		}
		if (totalMinutesAsleep > mostMinutesAsleep)
		{
			bestGuard = guard;
			mostMinutesAsleep = totalMinutesAsleep;
			bestMinute = minuteMostSlept;
		}
	}
	std::cout << "Best gaurd: " << bestGuard << " Number of minutes alseep: " << mostMinutesAsleep << " Minute most asleep: " << bestMinute << " Solution: " << bestGuard * bestMinute << std::endl;
	file.close();
}
