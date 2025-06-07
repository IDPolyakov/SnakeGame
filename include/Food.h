#pragma once
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Constants.h"
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

struct Segment;

class Food
{
public:
	Food();
	Food(const deque<Segment>& snake);
	void respawn(const deque<Segment>& snake);
	void draw(RenderWindow& window);

	ll x, y;
private:
	CircleShape shape;
};

