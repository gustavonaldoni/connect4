void DrawPlayAgainButton(Button* playAgainButton)
{
    float scaleFactor;

    scaleFactor = 4.0;

    playAgainButton->x = (GetScreenWidth() - scaleFactor * playAgainButton->texture.height) / 2;
    playAgainButton->y = GetScreenHeight() / 12;

    DrawTextureEx(playAgainButton->texture, (Vector2){playAgainButton->x, playAgainButton->y}, 0.0f, scaleFactor, RAYWHITE);
}

Rectangle GetPlayAgainButtonRec(Button button, float scaleFactor)
{
    return (Rectangle){button.x,
                       button.y,
                       button.texture.width * scaleFactor,
                       button.texture.height * scaleFactor};
}