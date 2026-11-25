#pragma once
// Tiny dependency-free unit-test framework (no network / GoogleTest needed).
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace mini {
struct Case { std::string name; std::function<void()> fn; };
inline std::vector<Case>& registry() { static std::vector<Case> r; return r; }
inline int& failures() { static int f = 0; return f; }
struct Registrar {
    Registrar(const char* n, std::function<void()> f) { registry().push_back({n, std::move(f)}); }
};
inline int runAll() {
    int failedCases = 0;
    for (const auto& c : registry()) {
        const int before = failures();
        c.fn();
        const bool ok = failures() == before;
        std::cout << (ok ? "[ PASS ] " : "[ FAIL ] ") << c.name << "\n";
        if (!ok) ++failedCases;
    }
    std::cout << registry().size() - failedCases << "/" << registry().size() << " tests passed\n";
    return failedCases == 0 ? 0 : 1;
}
}  // namespace mini

#define TEST(name) \
    static void name(); \
    static mini::Registrar registrar_##name(#name, name); \
    static void name()

#define CHECK(cond) do { if (!(cond)) { ++mini::failures(); \
    std::cerr << "    check failed " << __FILE__ << ":" << __LINE__ << ": " #cond "\n"; } } while (0)
#define CHECK_EQ(a, b) CHECK((a) == (b))
