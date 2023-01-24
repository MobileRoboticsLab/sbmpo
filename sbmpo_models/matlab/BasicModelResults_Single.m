%% SBMPO Results Visualizer

stats = sbmpo_stats("../results/basic_model/stats.csv");
plans = sbmpo_results("../results/basic_model/results.csv");
obstacles = sbmpo_obstacles("../results/basic_model/obstacles.csv");

% Convert path states to points and plot
for p = 1:length(plans)

    start = V(InitialState, p);
    goal = V(GoalState, p);
    goal_r = V(GoalThreshold, p);

    figure
    hold on
    axis([start(1)-2.5 goal(1)+2.5 start(2)-2.5 goal(2)+2.5])

    title(strcat("Results ", int2str(p)))
    xlabel("X (m)")
    ylabel("Y (m)")

    % Plot obstacles
    for o = 1:obstacles(p).n
        obs = [obstacles(p).x(o)-obstacles(p).r(o) obstacles(p).y(o)-obstacles(p).r(o) ...
            obstacles(p).r(o)*2 obstacles(p).r(o)*2];
        rectangle('Position', obs, 'Curvature', [1,1], 'FaceColor', 'k')
    end

    % Plot goal
    goal = [goal(1)-goal_r goal(2)-goal_r goal_r*2 goal_r*2];
    rectangle('Position', goal, 'Curvature', [1,1], 'FaceColor', 'b')

    % Plot all nodes
    bx = zeros(1, plans(p).buffer_size);
    by = zeros(1, plans(p).buffer_size);
    for b = 1:plans(p).buffer_size
        node = plans(p).nodes(b);
        bx(b) = node.state(1);
        by(b) = node.state(2);
    end
    plot (bx, by, 'xk', 'MarkerSize', 2)

    % Plot path
    px = zeros(1, plans(p).path_size);
    py = zeros(1, plans(p).path_size);
    for n = 1:plans(p).path_size
        node = plans(p).nodes(plans(p).path(n) + 1);
        px(n) = node.state(1);
        py(n) = node.state(2);
    end
    plot (px, py, '-g', 'LineWidth', 3)
    plot (px, py, 'ob', 'MarkerSize', 5)
end