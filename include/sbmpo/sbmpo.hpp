#ifndef SBMPO_SBMPO_HPP_
#define SBMPO_SBMPO_HPP_

#include <sbmpo/types/implicit_grid.hpp>
#include <sbmpo/types/node_queue.hpp>
#include <sbmpo/model.hpp>

namespace sbmpo {

enum ExitCode {GOAL_REACHED, ITERATION_LIMIT, NO_NODES_LEFT, MAX_GENERATIONS, INVALID_PATH, UNKNOWN_ERROR};

struct SBMPOParameters {
    int max_iterations, max_generations;
    float sample_time;
    std::vector<float> grid_resolution;
    State start_state, goal_state;
    std::vector<Control> samples;
};

class SBMPO {

    public:

    /// @brief Create a new SBMPO object
    /// @param model Model to run the planner on
    /// @param params SBMPO Parameters for planning
    SBMPO(Model &model, const SBMPOParameters &params);

    /// @brief Run the SBMPO planner
    void run();

    /// @brief Reset the SBMPO planner
    void reset();

    /// @brief Iteration count of planner
    /// @return Iteration value
    int iterations(){ return iterations_; }

    /// @brief Exit code of the plan run
    /// @return Value of the exit code
    ExitCode exit_code() { return exit_code_; }

    /// @brief Computation time of the plan run
    /// @return Time in microseconds
    time_t time_us() { return time_us_; }

    /// @brief Cost of the latest planner run
    /// @return Cost of the plan
    float cost() { return cost_; }

    /// @brief Number of nodes in plan run
    /// @return Size of implicit grid map
    size_t size() { return implicit_grid_->size(); }

    /// @brief Get the plan path in terms of Nodes
    /// @return List of Node pointers
    std::vector<Node::Ptr> node_path() { return node_path_; }

    /// @brief Get the plan path in terms of States
    /// @return List of States
    std::vector<State> state_path() { return state_path_; }

    /// @brief Get the plan path in terms of Controls
    /// @return List of Controls
    std::vector<Control> control_path() { return control_path_; }

    /// @brief Get all nodes in plan run
    /// @return List of Node pointers
    std::vector<Node::Ptr> all_nodes() { return implicit_grid_->nodes(); }

    /// @brief Get the implicit grid
    /// @return Pointer to implicit grid
    std::shared_ptr<ImplicitGrid> implicit_grid() { return implicit_grid_; }

    /// @brief Get the node queue
    /// @return Pointer to node queue
    std::shared_ptr<NodeQueue> node_queue() { return node_queue_; }

    private:

    Model * model_;
    SBMPOParameters parameters_;

    std::shared_ptr<ImplicitGrid> implicit_grid_;
    std::shared_ptr<NodeQueue> node_queue_;

    Node::Ptr start_node_;
    Node::Ptr next_node_;
    Node::Ptr best_node_;

    ExitCode exit_code_;
    int iterations_;
    time_t time_us_;
    float cost_;

    std::vector<Node::Ptr> node_path_;
    std::vector<State> state_path_;
    std::vector<Control> control_path_;

    // Initialize SBMPO run
    void initialize();

    // Generate children from node
    void generate_children(const Node::Ptr node);

    // Update node
    void update_node(const Node::Ptr node);

    // Generate path
    bool generate_path();

};

}

#endif