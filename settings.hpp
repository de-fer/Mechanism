#ifndef SETTINGS_H
#define SETTINGS_H

struct Window_settings
{
    bool fullscreen;
    int width, height;
    float bg_r, bg_g, bg_b, bg_a;

    bool RESIZABLE, //можно ли изменять размер окна пользователю
        DECORATED, //рамка окна, кнопка выкл, сворачивания и тд
        FOCUSED, //активное окно при создании
        FLOATING, //поверх всех окон
        MAXIMIZED, //максимальный размер
        CENTER_CURSOR, //удерживать курсор в центре
        TRANSPARENT_FRAMEBUFFER, //вкл альфа-канал
        MOUSE_PASSTHROUGH; //мышь тыкает сквозь окно
    int POSITION_X, POSITION_Y; //позиция окна по умолчанию (-9999 - любая позиция)
};

struct Camera_settings
{
    float size, //масштаб камеры
        speed, //скорость камеры
        speed_multiple; //скорость камеры при ускорении
    int near, //расстояние до ближней плоскости отсечения
        far; //расстояние до дальней плоскости отсечения
    float mouse_multiple; //чувствительность мыши
};

#endif // SETTINGS_H
