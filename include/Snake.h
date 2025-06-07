#pragma once
#include <bits/stdc++.h>
#include "Food.h"
#include <SFML/Graphics.hpp>
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

enum class Direction { Up, Down, Left, Right };

struct Segment
{
	ll x, y;
	Segment(ll x, ll y) : x(x), y(y) {}
};

class Snake
{
public:
    Snake();
    void handleInput();
    void update(Food& food, ld& delay);
    void draw(RenderWindow& window, ld alpha);
    bool checkCollision();
    ll getScore() const;
    const deque<Segment>& getBody() const;
private:
    deque<Segment> body, prevBody;
    Direction dir;
};

