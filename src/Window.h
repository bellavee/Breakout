
#ifndef WINDOW_H
#define WINDOW_H



class Window {
public:
    Window();
    ~Window();

    void Initialize(int width, int height);
    int Resize(int width, int height);
    void Update();
    void Render();

private:
    int _width, _height;

};



#endif //WINDOW_H
