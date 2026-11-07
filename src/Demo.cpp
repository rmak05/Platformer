//#include <SFML/Graphics.hpp>
//#include "Debug.hpp"
//using namespace std;
//using namespace sf;
//
//void test() {
//    debug::activate();
//
//    sf::RenderWindow window(sf::VideoMode(19u * 64u, 12u * 64u), "Master Window");
//    sf::View view1(sf::FloatRect(0.0f, 0.0f, 200.f, 300.f));
//    view1.setViewport(sf::FloatRect(0.0f, 0.0f, 0.5f, 1.0f));
//    sf::View view2(sf::FloatRect(700.0f, 0.0f, 200.f, 300.f));
//    view2.setViewport(sf::FloatRect(0.5f, 0.0f, 0.5f, 1.0f));
//
//    sf::CircleShape shape1(100.f);
//    shape1.setFillColor(sf::Color::Green);
//    sf::CircleShape shape2(100.f);
//    shape2.setFillColor(sf::Color::Green);
//    shape2.setPosition(700.0f, 0.0f);
//
//    sf::Texture grass_texture, brick_texture;
//    grass_texture.loadFromFile("Assets\\Textures\\bush.png");
//    brick_texture.loadFromFile("Assets\\Textures\\brick.png");
//
//    sf::Sprite grass[4];
//    grass[0].setTexture(grass_texture);
//    grass[0].setScale(4.0f, 4.0f);
//    grass[0].setOrigin(8.0f, 8.0f);
//    grass[0].setPosition(4.5f * 64.0f, 7.5f * 64.0f);
//    grass[1].setTexture(grass_texture);
//    grass[1].setScale(4.0f, 4.0f);
//    grass[1].setPosition(5.0f * 64.0f, 7.0f * 64.0f);
//    grass[2].setTexture(grass_texture);
//    grass[2].setScale(4.0f, 4.0f);
//    grass[2].setPosition(6.0f * 64.0f, 7.0f * 64.0f);
//    grass[3].setTexture(grass_texture);
//    grass[3].setScale(4.0f, 4.0f);
//    grass[3].setPosition(7.0f * 64.0f, 7.0f * 64.0f);
//
//    sf::Sprite brick[4];
//    brick[0].setTexture(brick_texture);
//    brick[0].setScale(4.0f, 4.0f);
//    brick[0].setPosition(4.0f * 64.0f, 8.0f * 64.0f);
//    brick[1].setTexture(brick_texture);
//    brick[1].setScale(4.0f, 4.0f);
//    brick[1].setPosition(5.0f * 64.0f, 8.0f * 64.0f);
//    brick[2].setTexture(brick_texture);
//    brick[2].setScale(4.0f, 4.0f);
//    brick[2].setPosition(6.0f * 64.0f, 8.0f * 64.0f);
//    brick[3].setTexture(brick_texture);
//    brick[3].setScale(4.0f, 4.0f);
//    brick[3].setPosition(7.0f * 64.0f, 8.0f * 64.0f);
//
//
//    while (window.isOpen()){
//        sf::Event event;
//
//        while (window.pollEvent(event)){
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            else if (event.type == sf::Event::MouseButtonPressed) {
//                if (event.mouseButton.button == sf::Mouse::Right) {
//                    debug::update();
//                }
//            }
//        }
//
//        window.clear(sf::Color::White);
//
//        /*window.setView(view1);
//        window.draw(shape1);
//        window.draw(shape2);
//        debug::draw(window);
//
//        window.setView(view2);
//        window.draw(shape1);
//        window.draw(shape2);
//        debug::draw(window);*/
//
//        //window.draw(shape1);
//        //window.draw(shape2);
//        for(auto& itr:grass) window.draw(itr);
//        for(auto& itr:brick) window.draw(itr);
//        debug::draw(window);
//
//        window.display();
//    }
//
//    debug::deactivate();
//}
//
//class A {
//public:
//    int a;
//
//    A() {
//        a=1000;
//    }
//
//    A(A&& b) noexcept{
//        a=b.a;
//    }
//};
//
//enum class poke {
//    fire,
//    water = 56,
//    fairy = 37,
//    dragon = 36,
//    grass = 37
//};
//
//void demo() {
//    sf::RenderWindow window(sf::VideoMode(19u * 64u, 12u * 64u), "Master Window");
//
//    while (window.isOpen()){
//        sf::Event event;
//
//        while (window.pollEvent(event)){
//            if      (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            else if (event.type == sf::Event::EventType::KeyPressed) {
//                std::cout << "Key Pressed: " << event.key.code << std::endl;
//            }
//            else if (event.type == sf::Event::EventType::KeyReleased) {
//                std::cout << "Key Released: " << event.key.code << std::endl;
//            }
//        }
//
//        
//
//        window.display();
//    }
//}
//
//int main(){
//    //test();
//    demo();
//    
//    return 0;
//}