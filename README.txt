A C++ project that implements a simple feedforward neural network (MLP) to classify 28×28 grayscale digit images.

Features-
Custom matrix operations (no external libraries)

2-layer MLP with ReLU and Softmax

Hardcoded weights for classification

CLI for predicting raw input images

Python scripts to visualize images

How to Use-
Build with make

Run with:

bash
Copy
Edit
./main images/im5
Visualize images using:

bash
Copy
Edit
python3 plot_img.py images/im5
Key Files-
main.cpp: Runs inference

MlpNetwork.*, Dense.*, Matrix.*: Core NN and math logic

images/: Sample input files

plot_img.py: Show input images

Learning Goals-
Understand how neural networks work internally

Implement matrix math and forward propagation from scratch
