

struct Scaleable {
    void (***vTable)(void*)   m_pvtable;
};

void Scaleable_DTOR();
void Scaleable_scale_double(double _f);


void (*vtable_Scaleable[])(void*) = { (void (*)(void*))Scaleable_DTOR,
                                      (void (*)(void*))Scaleable_scale_double };


int
main (int argc, char *argv[])
{
	
	return 0;
}
