clear;
load('gesture_dataset.mat');
k=7;
%% data preparation
%reshape each gesture to 600*3 data point
gesture_l = reshape(gesture_l,[size(gesture_l,1)*size(gesture_l,2) size(gesture_l,3)]);
gesture_o = reshape(gesture_o,[size(gesture_o,1)*size(gesture_o,2) size(gesture_o,3)]);
gesture_x = reshape(gesture_x,[size(gesture_x,1)*size(gesture_x,2) size(gesture_x,3)]);

%% classification with Kmeans and nubs
Exercise3_kmeans(gesture_l,gesture_o,gesture_x,init_cluster_l,init_cluster_o,init_cluster_x,k);
Exercise3_nubs(gesture_l,gesture_o,gesture_x,k);
