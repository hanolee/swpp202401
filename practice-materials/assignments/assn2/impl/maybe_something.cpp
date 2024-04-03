import maybe_something;

namespace maybe_something {
    size_t Something::global_num_objects = 0;
    size_t Nothing::global_num_objects = 0;

    Something::Something(const std::string& str) : content(str) {
        ++global_num_objects;
    }

    Something::Something(std::string&& str) : content(std::move(str)) {
        ++global_num_objects;
    }

    Something::Something(const Something& other) : content(other.content) {
        ++global_num_objects;
    }

    Something& Something::operator=(const Something& other) {
        if (this != &other) {
            content = other.content;
        }
        return *this;
    }

    Something::Something(Something&& other) noexcept : content(std::move(other.content)) {}

    Something& Something::operator=(Something&& other) noexcept {
        if (this != &other) {
            content = std::move(other.content);
        }
        return *this;
    }

    Something::~Something() {
        --global_num_objects;
    }

    std::string_view Something::view_content() const {
        return content;
    }

    size_t Something::count() noexcept {
        return global_num_objects;
    }

    Nothing::Nothing() {
        ++global_num_objects;
    }

    Nothing::Nothing(const Nothing& other) {}

    Nothing& Nothing::operator=(const Nothing& other) {
        return *this;
    }

    Nothing::Nothing(Nothing&& other) noexcept {}

    Nothing& Nothing::operator=(Nothing&& other) noexcept {
        return *this;
    }

    Nothing::~Nothing() {
        --global_num_objects;
    }

    size_t Nothing::count() noexcept {
        return global_num_objects;
    }

    MaybeSomething create_something_by_copying(const std::string& str) {
        return Something(str);
    }

    MaybeSomething create_something_by_moving(std::string&& str) {
        return Something(std::move(str));
    }

    MaybeSomething create_nothing() {
        return Nothing();
    }

    std::string_view view(const MaybeSomething& thing) {
        if (std::holds_alternative<Something>(thing)) {
            return std::get<Something>(thing).view_content();
        } else {
            return "empty";
        }
    }

    size_t count_siblings(const MaybeSomething& thing) {
        if (std::holds_alternative<Something>(thing)) {
            return Something::count();
        } else {
            return Nothing::count();
        }
    }
} // namespace maybe_something
