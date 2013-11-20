#include "RenderContextOGL3x.h"
#include "glfw3.h"

namespace ACTK {

	void RenderContextOGL3x::release(void)
	{
		LOG_INIT("OpenGL RenderContext released");
	}


	void RenderContextOGL3x::clear(const ClearState& clearState)
	{
		/* ToDo: Das übergebene ClearState objekt enhält die Parameter auf die die der Context eingestellt werden muss.
		* Wichtig ist dabei, dass man einen State nicht nochmal ändert, wenn der OpenGL-Wert bereits auf den Wert, den man haben möchte gestellt ist.
		*
		* Z.B.: Wenn man in einem Frame die Clearcolor auf Rosa gestellt hat, sollte man sich das merken und beim nächsten Aufruf sollte
		* die Clearcolor nicht nochmal auf rosa gestellt werden. Die OpenGL-Clearcolor sollte nur geändert werden und die OpenGL funktion nur aufgerufen werden, wenn man tatsächlich die Farbe ändert und nicht immer wieder die selbe Farbe übergibt.
		* Durch solche sinnlosen Aufrufe hat man nichts am OpenGL-State verändert aber kostbare Zeit verschenkt.
		* 
		* Deshalb sollte man sich im RenderContextOGL3x den Clearstate, den man zuletzt gesetzt hat speichern oder ein eigenes Schatten ClearState-Objekt führen, das sich merkt,
		* welchen Zustand OpenGL gerade hat und bei jeder Änderung des OpenGL-State sollte die Schattenkopie mitgeändert werden, denn das Nachfragen über OpenGL-Funktionen welcher 
		* State gerade gesetzt ist, ist genau so teuer wie es sinnlos zu ändern.
		*/
	}


	void RenderContextOGL3x::swapBuffers(void)
	{
		// ToDo: einfach bffer wechseln
	}

}