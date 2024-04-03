module;
#include <algorithm>
#include <concepts>
#include <expected>
#include <vector>

export module collect;

namespace collect {
export template <std::movable T, std::movable E>
std::expected<std::vector<T>, E>
    collect_expected(const std::vector<std::expected<T, E>>& inputs) {
        // Initialize the result vector
        std::vector<T> result;
        
        // Loop through the input vector
        for (const auto& item : inputs) {
            // If any of the expected contains error, return the error immediately
            if (!item.has_value()) {
                return std::unexpected<E>(item.error());
            }
            // Otherwise, add the value to the result vector
            result.push_back(item.value());
        }
        
        // Return the result vector as an expected value
        return result;
    }

    export template <std::movable T, std::movable E>
    std::expected<std::vector<T>, E>
    move_collect_expected(std::vector<std::expected<T, E>>&& inputs) {
        // Initialize the result vector
        std::vector<T> result;
        
        // Reserve memory for the result vector to avoid unnecessary reallocations
        result.reserve(inputs.size());
        
        // Loop through the input vector
        for (auto&& item : inputs) {
            // If any of the expected contains error, return the error immediately
            if (!item.has_value()) {
                return std::unexpected<E>(item.error());
            }
            // Otherwise, move the value to the result vector
            result.push_back(std::move(item).value());
        }
        
        // Return the result vector as an expected value
        return result;
    }
} // namespace collect
