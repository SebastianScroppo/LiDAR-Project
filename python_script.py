import serial
import numpy as np
import open3d as o3d

if __name__=="__main__":

    f= open("demofile2dx4.txt","w")

    for x in range(10):
        f.write('{0:d} 0 0\n'.format(x))
        f.write('{0:d} 0 1\n'.format(x))
        f.write('{0:d} 1 0\n'.format(x))
        f.write('{0:d} 1 1\n'.format(x))
    f.close()

    print("testing IO for point cloud ...")
    pcd = o3d.io.read_point_cloud("wack.xyz", format='xyz')

    print(pcd)

    print(np.asarray(pcd.points))

    pt1=0
    pt2=1
    pt3=2
    pt4=3
    po=0

    lines=[]

    for x in range(64):
        lines.append([pt1+po,pt2+po])
        lines.append([pt2+po,pt3+po])
        lines.append([pt3+po,pt4+po])
        lines.append([pt4+po,pt1+po])
        po += 4;

    pt1=0
    pt2=1
    pt3=2
    pt4=3
    po=0
    do=4

    for x in range(5):
        lines.append([pt1+po,pt1+do+po])
        lines.append([pt2+po,pt2+do+po])
        lines.append([pt3+po,pt3+do+po])
        lines.append([pt4+po,pt4+do+po])
        po += 4;

    line_set=o3d.geometry.LineSet(points=o3d.utility.Vector3dVector(np.asarray(pcd.points)), lines=o3d.utility.Vector2iVector(lines))

    o3d.visualization.draw_geometries([line_set])

print("done")

s = serial.Serial("COM4", 115200)
txtfile = open(r"C:\Users\scroppos\Desktop\xyzfile.xyz", "w+")
xval=0;
theta=0;
iterations=5

print("Opening: " + s.name)

for j in range(iterations): #how many points you want to take
    print("Press Button For Iteration # " + str(j))

    for i in range(32):
        x = s.readline() #read one line of bytes     
        c = x.decode() #turn to str
        r = float(c.strip('/r/n')); #turn to float
        yval = r*np.sin(theta*np.pi/180);
        zval = r*np.cos(theta*np.pi/180);
        print(c, end=" ")
        txtfile.write('%d %.2f %.2f\n' % (xval, yval, zval));
        theta += 11.25;

    xval+=200;

print("Closing: " + s.name)
txtfile.close();
s.close();
