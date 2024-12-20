#ifndef SBMPO_BENCHMARK_OBSTACLE2D_MODEL_HPP_
#define SBMPO_BENCHMARK_OBSTACLE2D_MODEL_HPP_

#include <sbmpo/types/types.hpp>
#include <sbmpo/types/Model.hpp>

namespace sbmpo_benchmarks
{
    using namespace sbmpo;

    using Obstacles = std::vector<std::array<float, 3>>;

    template <typename ModelType, typename... Args>
    class Obstacle2DModel : public ModelType
    {
        static_assert(std::is_base_of<Model, ModelType>::value, "ModelType must be a subclass of Model.");

    public:
        Obstacle2DModel(Args &&...args)
            : ModelType(std::forward<Args>(args)...)
        {
            body_radius_ = 0.25f;
            map_bounds_ = {-10.0f, -10.0f, 10.0f, 10.0f};
        }

        void set_obstacles(Obstacles obstacles)
        {
            obstacles_ = obstacles;
        }

        void set_body_radius(float body_radius)
        {
            body_radius_ = body_radius;
        }

        // Array of 4 boundary values ([xmin ymin xmax ymax])
        void set_map_bounds(std::array<float, 4> map_bounds)
        {
            map_bounds_ = map_bounds;
        }

        // Determine if node is valid (with obstacles and map bounds)
        bool is_valid(const State &state) override
        {
            // Check model function
            if (!ModelType::is_valid(state))
                return false;

            // Bound check
            if (state[0] - map_bounds_[0] < body_radius_ ||
                state[1] - map_bounds_[1] < body_radius_ ||
                map_bounds_[2] - state[0] < body_radius_ ||
                map_bounds_[3] - state[1] < body_radius_)
                return false;

            // Obstacle collision check
            for (size_t o = 0; o < obstacles_.size(); o++)
            {
                const float dx = state[0] - obstacles_[o][0];
                const float dy = state[1] - obstacles_[o][1];
                const float threshold = obstacles_[o][2] + body_radius_;
                if (dx * dx + dy * dy < threshold * threshold)
                    return false;
            }

            return true;
        }

    protected:
        float body_radius_;
        std::array<float, 4> map_bounds_;
        Obstacles obstacles_;
    };

}

#endif