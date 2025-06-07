#pragma once
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Food.h"
#include "Snake.h"
//❤//
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//❤//
#define full cin.tie(0);std::ios::sync_with_stdio(false);
//❤//
#define pb push_back
#define mp make_pair
//❤//
#define INF numeric_limits<ll>::max()
#define EPS 100000000000000007
//❤//
#define vi vector<ll>
#define vvi vector<vector<ll>>
#define vd vector<ld> 
//❤//
#define all(a) a.begin(), a.end()
#define endl "\n"
//❤//
using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	void run();
private:
	void proccesEvents();
	void update();
	void render();
	void reset();

	RenderWindow window;
	Clock clock;
	Font font;
	Snake snake;
	Food food;
	ld timer, delay;
};

