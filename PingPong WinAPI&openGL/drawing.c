#include "drawing.h"

void drawTriangle(Vector3_t c1, Vector3_t c2, Vector3_t c3, Color4_t color, window* window)
{

	long offsetX = (long)window->offsetX;
	long offsetY = (long)window->offsetY;

	glColor4f(color.r, color.g, color.b, color.a);
	glBegin(GL_TRIANGLES);
	glVertex3f(c1.x + offsetX, c1.y + offsetY, c1.z);
	glVertex3f(c2.x + offsetX, c2.y + offsetY, c2.z);
	glVertex3f(c3.x + offsetX, c3.y + offsetY, c3.z);
	glEnd();
}
void drawRect(rect* coords, Color4_t* c, rect* textureCoords, texture* tex, long depth, window* window)
{
	// Nak�adamy mask� koloru lub resetujemy j� do braku maski - 1,1,1,1.
	if (c != NULL)
	{
		glColor4f(c->r, c->g, c->b, c->a);
	}
	else
	{
		glColor4f(1.f, 1.f, 1.f, 1.f);
	}

	// Je�li podali�my tekstur� przygotujmy OpenGL do wyrenderowania jej na prostok�cie.
	if (tex != NULL)
	{
		// Ustawmy o kt�r� tekstur� nam chodzi.
		glBindTexture(GL_TEXTURE_2D, (GLuint)tex->pointer);

		// W��czmy alpha blending (prze�roczysto��) je�li tekstura j� obs�uguje.
		if (tex->flags & TEXTURE_FLAG_ALPHA_BLEND)
		{
			// W��czamy funckje blendowania.
			glEnable(GL_BLEND);
			// Funckja wyliczania prze�roczysto�ci 1 - kana� alfa tekstury.
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		// Odbijmy tekstur� po osi Y bo specyfikacja OpenGL ma odwr�con� o� Y w stosunku do bitmapy naszej tekstury.
		glMatrixMode(GL_TEXTURE); // Ustawiamy macierz na kt�rym b�dziemy operowa� (GL_TEXTURE).
		glLoadIdentity(); // Wczytujemy macierz {1, 0, 0, 0} {0, 1, 0, 0} {0, 0, 1, 0} {0, 0, 0, 1} (identity).
		glScalef(1.0f, -1.0f, 1.0); // Mno�ymy identity matrix przez 1 -1 1 czyli odbijamy o� Y.

		// Uruchamiamy modu� teksturowania.
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// Rozpoczynamy rysowanie prostok�ta.
	glBegin(GL_QUADS);

	// Nak�adamy wierzcho�ek tekstury je�li istnieje tX, tY.
	if (tex != NULL)
	{
		glTexCoord2f(textureCoords->x, textureCoords->y);
	}
	// Tworzymy pierwszy wierzcho�ek ptostok�ta X, Y.
	glVertex3f(coords->x, coords->y, 0.0f);

	// Analogicznie tekstura na tX + tW, tY.
	if (tex != NULL)
	{
		glTexCoord2f(textureCoords->x + textureCoords->w, textureCoords->y);
	}
	// Wierzcho�ek X + W, Y.
	glVertex3f(coords->x + coords->w, coords->y, 0.0f);

	// Tekstura na tX + tW, tY + tW.
	if (tex != NULL)
	{
		glTexCoord2f(textureCoords->x + textureCoords->w, textureCoords->y + textureCoords->h);
	}
	// Wierzcho�ek X + W, Y + H.
	glVertex3f(coords->x + coords->w, coords->y + coords->h, 0.0f);

	// Tekstura na tX, tY + tH.
	if (tex != NULL)
	{
		glTexCoord2f(textureCoords->x, textureCoords->y + textureCoords->h);
	}
	glVertex3f(coords->x, coords->y + coords->h, 0.0f);

	// Ko�czymy renderowanie prostok�ta.
	glEnd();

	// Pora na clean up.
	// Je�li u�ywali�my tekstur / blendowania (prze�roczysto�ci) musimy je wy��czy�.
	if (tex != NULL)
	{
		if (tex->flags & TEXTURE_FLAG_ALPHA_BLEND)
		{
			// Wy��czamy modu� blendowania.
			glDisable(GL_BLEND);
		}

		// Wy��czamy modu� teksturowania.
		glDisable(GL_TEXTURE_2D);
		// Resetujemy u�ywan� teksture (ustawiamy na 0 = brak tekstury).
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}

void drawCircle(long x, long y, long r, int vCount, Color4_t* color, long depth, window* window)
{
	long offsetX = (long)window->offsetX;
	long offsetY = (long)window->offsetY;

	float angle = 360.0 / (float)vCount;

	glColor4f(color->r, color->g, color->b, color->a);
	glBegin(GL_TRIANGLE_FAN); 
	for (int i = 0; i < vCount; i++)
	{
		float curr_angle = i * angle;
		long _x = r * cosf(i * 2.0*3.14 / vCount) + x;
		long _y = r * sinf(i * 2.0 * 3.14 / vCount) + y;
		long _z = depth; 
		glVertex3f(_x + offsetX, _y + offsetY, depth);
	}
  
	glEnd();

}

void loadTexture(texture* out, Image* image)
{
	GLint tex; // ID tekstury.

	glGenTextures(1, &tex); // Generujemy ID tekstury.

	glBindTexture(GL_TEXTURE_2D, tex); // M�wimy OpenGL-owi z kt�rej tekstury chcemy korzysta�.

	// Ustawiamy filtr skalowania w g�r�.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Ustawiamy filtr skalowania w d�.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Kopiujemy z RAM-u do vRAMU surowe piskele obrazu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei)image->width, (GLsizei)image->height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, image->data);

	// Ustawiamy pomocnicze informacje w naszej strukturze texture.
	out->pixelHeight = image->height;
	out->pixelWidth = image->width; 
	out->pointer = (void*)tex; // Uchwyt systemowy do tekstury.
	out->flags = 0;
	
}

void free_texture(texture* txt)
{
	glDeleteTextures(1, &txt->pointer);
}