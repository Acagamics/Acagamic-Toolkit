#include "ICleanableObserver.h"

namespace ACTK
{
	enum class UniformDatatype : char
	{
		// Artur's stuff
	};

	class UniformOGL3x : public ICleanable
	{
	public:
		// Update method
		UniformOGL3x(int location, UniformDatatype datatype, ICleanableObserver* observer) : 
			m_dirty(false),
			Location(location),
			Datatype(datatype),
			m_observer(observer)
		{}

		~UniformOGL3x();

		virtual void clean() = 0;

		const int				Location;
		const UniformDatatype	Datatype;

	private:

		bool					m_dirty;
		ICleanableObserver*		m_observer;
	};
}