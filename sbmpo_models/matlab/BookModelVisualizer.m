%% SBMPO Results Visualizer

% Set obstacles
obstacles = [3.1, 1.2, 0.5;
             3.5, 3.7, 0.5;
             1.0, 0.5, 0.5];

% Set goal
goal = [5, 5, 0.3];

% Convert path states to points and plot
for p = 1:length(plans)

    figure
    hold on
    grid on
    axis([-2.5 7.5 -2.5 7.5])

    title(strcat("Results ", int2str(p)))
    xlabel("X (m)")
    ylabel("Y (m)")

    % Plot obstacles
    obs = [obstacles(:,1:2)-obstacles(:,3) obstacles(:,3).*2 obstacles(:,3).*2];
    for o = 1:length(obstacles)
        rectangle('Position',obs(o, :), 'Curvature', [1,1], 'FaceColor', 'k')
    end

    % Plot goal
    gol = [goal(1:2)-goal(3) goal(3)*2 goal(3)*2];
    rectangle('Position', gol, 'Curvature', [1,1], 'FaceColor', 'b')

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

    saveas(gcf, strcat('figures/book_model_result', int2str(p) ,'.png'));
end