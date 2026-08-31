struct IOS {
    static constexpr int siz = 1 << 21;
    char ibuf[siz], obuf[siz], *s = ibuf, *t = ibuf, *o = obuf, op[1 << 7];
#if ONLINE_JUDGE
    #define gc() (s == t && (t = (s = ibuf) + fread(ibuf, 1, siz, stdin), s == t)? -1 : *s++)
    #define pc(x) ((o - obuf < siz)? ((*o++) = x) : (fwrite(obuf, o - obuf, 1, stdout), o = obuf, (*o++) = x))
#else
    #define gc() getchar()
    #define pc(x) putchar(x)
#endif
    template<typename T> IOS& operator >> (T &x) {
        bool f = 0; int ch;
        for (; !isdigit(ch = gc()); ) {
            if (ch == -1) return *this;
            if (ch == 45) f = 1;
        }
        for (x = ch - 48; isdigit(ch = gc()); x = x * 10 + ch - 48);
        f && (x = -x); return *this;
    }
    template<typename T> IOS& operator << (T x) {
        if (!x) {pc(48); return *this; }
        if (x < 0) x = -x, pc(45);
        int len = 0;
        while (x) op[len++] = x % 10 + 48, x /= 10;
        while (len--) pc(op[len]); return *this;
    }
    IOS& operator >>(char& x) { do { x = gc(); } while (x == '\n'); return *this; }
    IOS& operator << (const char &x) { pc(x); return *this; }
    ~IOS() { fwrite(obuf, o - obuf, 1, stdout); }
#undef gc
#undef pc
} io;