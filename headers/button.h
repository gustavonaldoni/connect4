typedef struct
{
    int x, y;
    Texture2D texture;
    
} Button;

void DrawButton(Button button, float scaleFactor)
{
    DrawTextureEx(button.texture, (Vector2){button.x, button.y}, 0, scaleFactor, RAYWHITE);
}

void DrawTopRightButtons(Button buttons[3])
{
    int i, space;
    float scaleFactor;

    space = 15;
    scaleFactor = 3;

    for (i = 0; i < 3; i++)
    {
        buttons[i].x = GetScreenWidth() - (i + 1) * (space + buttons[i].texture.width * scaleFactor);
        buttons[i].y = space;

        DrawButton(buttons[i], scaleFactor);
    }
}

Rectangle GetTopRightButtonRec(int index, Button topRightButtons[3], float scaleFactor)
{
    return (Rectangle){topRightButtons[index].x, 
                        topRightButtons[index].y, 
                        topRightButtons[index].texture.width * scaleFactor, 
                        topRightButtons[index].texture.height * scaleFactor};
}
