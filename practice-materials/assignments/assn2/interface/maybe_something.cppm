module;
#include <cstdint>
#include <string>
#include <string_view>
#include <variant>

export module maybe_something;

namespace maybe_something {
    class Something {
    private:
        static size_t global_num_objects;
        std::string content;

    public:
        Something(const std::string& str);
        Something(std::string&& str); 
        Something(const Something& other); 
        Something& operator=(const Something& other);
        Something(Something&& other) noexcept; 
        Something& operator=(Something&& other) noexcept; 
        ~Something();

        std::string_view view_content() const;
        static size_t count() noexcept;
    };

    class Nothing {
    private:
        static size_t global_num_objects;

    public:
        Nothing(); 
        Nothing(const Nothing& other); 
        Nothing& operator=(const Nothing& other);
        Nothing(Nothing&& other) noexcept;
        Nothing& operator=(Nothing&& other) noexcept; 
        ~Nothing();

        static size_t count() noexcept;
    };

    export using MaybeSomething = std::variant<Nothing, Something>;

    MaybeSomething create_something_by_copying(const std::string& str);
    MaybeSomething create_something_by_moving(std::string&& str); 
    MaybeSomething create_nothing(); 
    std::string_view view(const MaybeSomething& thing);
    size_t count_siblings(const MaybeSomething& thing);
}
