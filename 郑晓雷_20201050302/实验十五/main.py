import torch
import torch.nn as nn
import numpy as np
import torchvision
import matplotlib.pyplot as plt
from torch.utils.data import DataLoader
from torch.utils.data import Dataset

torch.manual_seed(10)
device = "cuda" if torch.cuda.is_available() else "cpu"
losses=[]
accurancy=[]
class train_DealDataset(Dataset):
    """
        下载数据、初始化数据
    """
    def __init__(self):
        super(train_DealDataset, self).__init__()
        file = open('trainData.txt', 'r')
        train_x=[[]]
        train_y=[[]]
        for line in file.readlines():
            a=line.split()
            x=list(map(float,a[0:5]))
            y=[]
            y.append(float(a[5]))
            train_x.append(x)
            train_y.append(y)
        train_x.pop(0)
        train_y.pop(0)
        self.len = len(train_x)
        self.x_data=torch.tensor(train_x)
        self.y_data=torch.tensor(train_y)

    def __getitem__(self, index):
            return self.x_data[index], self.y_data[index]

    def __len__(self):
            return self.len

class test_DealDataset(Dataset):
        """
            下载数据、初始化数据
        """

        def __init__(self):
            super(test_DealDataset, self).__init__()
            file = open('testData.txt', 'r')
            test_x = [[]]
            test_y = [[]]
            for line in file.readlines():
                a = line.split()
                x = list(map(float, a[0:5]))
                y = []
                y.append(float(a[5]))
                test_x.append(x)
                test_y.append(y)
            test_x.pop(0)
            test_y.pop(0)
            self.len = len(test_x)
            self.x_data = torch.tensor(test_x)
            self.y_data = torch.tensor(test_y)

        def __getitem__(self, index):
           return self.x_data[index], self.y_data[index]

        def __len__(self):
           return self.len

dealDataset = train_DealDataset()
train_dataloader = DataLoader(dealDataset,8)
testDataset = test_DealDataset()
test_dataloader = DataLoader(testDataset, 8)


class LR(nn.Module):
    def __init__(self):
        super(LR, self).__init__()
        self.linear_relu1 = nn.Linear(5, 128)
        self.linear_relu2 = nn.Linear(128, 256)
        self.linear_relu3 = nn.Linear(256, 256)
        self.linear_relu4 = nn.Linear(256, 256)
        self.linear5 = nn.Linear(256, 1)
        self.relu = nn.ReLU()

    def forward(self, x):
        x = self.linear_relu1(x)
        x = self.relu(x)
        x = self.linear_relu2(x)
        x = self.relu(x)
        x = self.linear_relu3(x)
        x = self.relu(x)
        x = self.linear_relu4(x)
        x = self.relu(x)
        x = self.linear5(x)
        return x

lr_net = LR().to(device)

loss_fn = nn.MSELoss(reduction='mean')#选择损失函数

lr = 1e-3  # 学习率
optimizer = torch.optim.SGD(lr_net.parameters(),lr,0.9)

def train(dataloader, model, loss_fn, optimizer):
    size = len(dataloader.dataset)
    model.train()
    for batch, (X, y) in enumerate(dataloader):
        X, y = X.to(device), y.to(device)
        pred = model(X)
        loss = loss_fn(pred, y)
        losses.append(loss.item())

        # Backpropagation
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if batch % 10 == 0:
            loss, current = loss.item(), batch * len(X)
            print(f"loss: {loss:>7f}  [{current:>5d}/{size:>5d}]")

def test(dataloader, model, loss_fn):
    size = len(dataloader.dataset)
    num_batches = len(dataloader)
    model.eval()
    test_loss, correct = 0, 0
    with torch.no_grad():
        for X, y in dataloader:
            X, y = X.to(device), y.to(device)
            pred = model(X)
            test_loss += loss_fn(pred, y).item()
            y_new=y[:,0]
            correct += float((pred == y_new).sum())  # 计算正确预测的样本个数
    test_loss /= num_batches
    correct /= size
    print(f"Test Error: \n Accuracy: {(100*correct):>0.1f}%, Avg loss: {test_loss:>8f} \n")
    accurancy.append(correct*100)



def plot_losses(losses):
    plt.figure(1)
    losses=np.array(losses)

    window_size = 10
    i = 0
    moving_averages = []
    while i < len(losses) - window_size + 1:
        window_average = round(np.sum(losses[
                                      i:i + window_size]) / window_size, 2)
        moving_averages.append(window_average)
        i += 1

    plt.plot(range(len(moving_averages)), moving_averages, 'b--')
    plt.xlabel('step number')
    plt.ylabel('Training loss')
    plt.title('step number vs Training loss')

    plt.figure(2)
    plt.plot(range(len(accurancy)), accurancy, 'b--')
    plt.xlabel('step number')
    plt.ylabel('Accurancy')
    plt.title('step number vs Test Accurancy')

    plt.show()


epochs = 100
for t in range(epochs):
    print(f"\nEpoch {t+1}\n-------------------------------")
    train(train_dataloader, lr_net, loss_fn, optimizer)
    test(test_dataloader, lr_net, loss_fn)
plot_losses(losses)