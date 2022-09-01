void DrawTextureRotation(Texture2D, int, int, float, float);

void DrawTextureRotation(Texture2D texture, int x, int y, float angle, float scaleFactor)
{
    Rectangle sourceRec, destinationRec;
    Vector2 origin;

    sourceRec = (Rectangle){0, 0, texture.width, texture.height};
    destinationRec = (Rectangle){x, y, texture.width * scaleFactor, texture.height * scaleFactor};
    origin = (Vector2){(float)(texture.width / 2 * scaleFactor), (float)(texture.height / 2 * scaleFactor)};
    
    DrawTexturePro(texture, sourceRec, destinationRec, origin, GetTime() * angle, WHITE);
}