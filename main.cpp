#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

vector<tuple<double, int, int>> v;
set<pair<int, int>> s;

int width = 1600, height = 1000, cellsize = 100;
vector<sf::Vector2f> grid[160];
int a[] = { -1, 1, -width / cellsize, width / cellsize,
            -width / cellsize - 1, -width / cellsize + 1,
            width / cellsize - 1, width / cellsize + 1,0 };

class Pauk {
private:
    sf::Vector2f poz;
    sf::CircleShape glava;
    sf::VertexArray linija;

public:
    Pauk(float poz_x, float poz_y) {
        poz = { poz_x, poz_y };
        linija = sf::VertexArray(sf::Lines, 2);
    }

    void crtaj(sf::RenderWindow& window) {
        glava.setOrigin(poz);
        for (int i = 20; i >= 1; i--) {
            glava.setRadius(i);
            glava.setPosition(poz);
            glava.setOrigin(i, i);
            glava.setFillColor(sf::Color(0, 0, 255 - 12 * i));
            window.draw(glava);
        }

        int cf = (int)poz.x / cellsize;
        int bf = (int)width / cellsize;
        int dk = (int)poz.y / cellsize;
        int index = cf + bf * dk;
       

        while (v.size() < 8) {
            tuple<double, int, int> dis = { 0, 0, 0 };
            for (int j = 0; j < 9; j++) {
                int temp = index + a[j];
                if (temp >= 0 && temp < 160) {
                    for (auto& i : grid[temp]) {
                        double dist = sqrt((i.x - poz.x) * (i.x - poz.x) + (i.y - poz.y) * (i.y - poz.y));
                        if (get<0>(dis) == 0 || dist < get<0>(dis)) {
                            if (s.find({ i.x, i.y }) == s.end()) {
                                dis = { dist, i.x, i.y };
                            }
                        }
                    }
                }
            }

            if (get<0>(dis) != 0) {
                s.insert({ get<1>(dis), get<2>(dis) });
                v.push_back(dis);
            }
        }

        linija[0].position = poz;
        for (auto& i : v) {
            linija[1].position = sf::Vector2f(get<1>(i), get<2>(i));
            window.draw(linija);
        }
    }
    void promena(float pozx, float pozy) {
        float angle = atan2(pozy - poz.y, pozx - poz.x);
        poz.x += cos(angle)*3; 
        poz.y += sin(angle)*3; 

        vector<int> rem;
        for (int j = 0; j < v.size(); j++) {
            tuple<double, int, int> i = v[j];
            get<0>(v[j]) = sqrt((get<1>(i) - poz.x) * (get<1>(i) - poz.x) + (get<2>(i) - poz.y) * (get<2>(i) - poz.y));
            if (get<0>(v[j]) > 125)
                rem.push_back(j);
        }

        for (int i = rem.size() - 1; i >= 0; i--) {
            cout << s.size() << endl;
            s.erase({ get<1>(v[rem[i]]), get<2>(v[rem[i]])});
            v.erase(v.begin() + rem[i]);
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "PAUK", sf::Style::Default);
    window.setFramerateLimit(60);
    sf::CircleShape tc(2);
    tc.setFillColor(sf::Color::White);
    sf::Event ev;
    sf::Mouse mouse;
    
    int numOfDots = 1000;
    float pozm = 0, pozy = 0;
    vector<sf::Vector2f> tacka;
    int smt = width / cellsize * height * cellsize;

    for (int i = 0; i < numOfDots; i++) {
        int wx = rand() % width;
        int wy = rand() % height;
        tacka.push_back({ (float)wx, (float)wy });
    }

    for (int i = 0; i < numOfDots; i++) {
        int cf = (int)tacka[i].x / cellsize;
        int bf = (int)width / cellsize;
        int dk = (int)tacka[i].y / cellsize;
        int k = cf + bf * dk;
        grid[k].push_back(tacka[i]);
    }
   
    Pauk l = { (float)200, (float)200 };

    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();
            else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
                window.close();
            else if (ev.type == sf::Event::MouseMoved) {
                pozm = mouse.getPosition(window).x;
                pozy = mouse.getPosition(window).y;
            }
        }

        window.clear();

        for (int i = 0; i < numOfDots; i++) {
            tc.setPosition(tacka[i]);
            window.draw(tc);
        }

        l.crtaj(window);

        l.promena(pozm, pozy);

        window.display();
    }

    return 0;
}
