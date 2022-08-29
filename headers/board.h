int GetBoardX(Texture2D boardTexture, float scaleFactor);
int GetBoardY(Texture2D boardTexture, float scaleFactor);

typedef struct
{
    int canvas[6][7];
} Board;

int GetBoardX(Texture2D boardTexture, float scaleFactor)
{
    return (GetScreenWidth() - scaleFactor * boardTexture.width) / 2;
}

int GetBoardY(Texture2D boardTexture, float scaleFactor)
{
    return GetScreenHeight() - scaleFactor * boardTexture.height;
}

void ResetBoard(Board *board)
{
    int i, j;

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 7; j++)
        {
            (*board).canvas[i][j] = 0;
        }
    }
}

void DrawBoard(Board board, Texture2D boardTexture, Texture2D yellowPieceTexture, Texture2D redPieceTexture)
{
    int i, j;
    int x, y;
    int space;

    int boardX, boardY;
    float scaleFactor;

    scaleFactor = 6;

    boardX = GetBoardX(boardTexture, scaleFactor);
    boardY = GetBoardY(boardTexture, scaleFactor);

    Vector2 boardPosition = {boardX, boardY};

    DrawTextureEx(boardTexture, boardPosition, 0, scaleFactor, RAYWHITE);

    space = 5;

    x = boardX + (space * scaleFactor);
    y = boardY + (space * scaleFactor);

    for (i = 0; i < 6; i++)
    {
        x = boardX + (space * scaleFactor);

        for (j = 0; j < 7; j++)
        {
            if (board.canvas[i][j] == 1)
            {
                DrawTextureEx(yellowPieceTexture, (Vector2){x, y}, 0, scaleFactor, RAYWHITE);
            }

            else if (board.canvas[i][j] == 2)
            {
                DrawTextureEx(redPieceTexture, (Vector2){x, y}, 0, scaleFactor, RAYWHITE);
            } 

            x += (space + yellowPieceTexture.width - 2) * scaleFactor;
        }

        y += (space + yellowPieceTexture.height - 2) * scaleFactor;
    }
}
