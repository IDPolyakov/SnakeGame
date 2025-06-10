#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
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

class Menu 
{
public:
	Menu(ld width, ld height, const Font& font, const Texture& back);
	void draw(RenderWindow& window);
	void moveUp();
	void moveDown();
	ll getSelectedIndex() const;
	void setBackground(RenderWindow& window);
	void playConfirmSound();
private:
	Clock clock;
	Text title;
	ll selectedIndex;
	vector<Text> menuItems;
	Sprite Background;
	Music choiceSound, confirmSound;
};