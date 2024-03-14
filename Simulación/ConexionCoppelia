import sim
import time
import math
import numpy as np
import matplotlib.pyplot as plt

def set_joint_velocity(clientID, joint_handles, target_velocity):
    for joint_handle, target_velocity in zip(joint_handles,target_velocity):
        sim.simxSetJointTargetVelocity(clientID, joint_handle, target_velocity, sim.simx_opmode_oneshot)
        
def connect_to_coppelia():
    sim.simxFinish(-1)  # Cerrar todas las conexiones existentes
    clientID = sim.simxStart('127.0.0.1', 19997, True, True, 5000, 5)  # Conéctate a CoppeliaSim por medio del Cube en la simulación
    if clientID != -1:
        print('Conectado a CoppeliaSim')
    else:
        print('No se pudo conectar')
    return clientID

def disconnect_from_coppelia(clientID):
    sim.simxFinish(clientID)

def set_joint_positions(clientID, joint_handles, target_positions):
    for joint_handle, target_position in zip(joint_handles, target_positions):
        sim.simxSetJointTargetPosition(clientID, joint_handle, target_position, sim.simx_opmode_oneshot)
        # Mueve el vector de los grados de libertad a la posición indicada

def interpolate(start, end, steps):
    step_size = [(end[i] - start[i]) / steps for i in range(len(start))]
    interpolated_positions = [[start[i] + step_size[i] * j for i in range(len(start))] for j in range(steps)]
    return interpolated_positions
    # Nos entrega la posición a la que tiene que ir en cada interacción el robot.

def plot_trajectories(time_values, positions_values, velocities_values):
    plt.figure(figsize=(16, 12))

    # Convertir las listas a matrices NumPy
    positions_matrix = np.array(positions_values)
    velocities_matrix = np.array(velocities_values)

    # Plot de las posiciones
    plt.subplot(2, 1, 1)
    for i, positions in enumerate(positions_matrix.T):
        plt.plot(time_values, positions, label=f'Joint {i+1} Posición')

    plt.title('Trayectorias de las Posiciones')
    plt.xlabel('Tiempo (s)')
    plt.ylabel('Valor')
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))  # Coloca la leyenda a la derecha
    plt.grid(True)

    # Plot de las velocidades
    plt.subplot(2, 1, 2)
    for i, velocities in enumerate(velocities_matrix.T):
        plt.plot(time_values, velocities, linestyle='--', label=f'Joint {i+1} Velocidad')

    plt.title('Trayectorias de las Velocidades')
    plt.xlabel('Tiempo (s)')
    plt.ylabel('Valor')
    plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))  # Coloca la leyenda a la derecha
    plt.grid(True)

    plt.tight_layout()
    plt.show()

def main():
    global listaPositions, listaVelocities
    clientID = connect_to_coppelia()
    if clientID != -1:
        # Obtener los handles de los joints del robot
        _, joint1 = sim.simxGetObjectHandle(clientID, 'JointX', sim.simx_opmode_oneshot_wait)
        _, joint2 = sim.simxGetObjectHandle(clientID, 'JointY', sim.simx_opmode_oneshot_wait)
        _, joint3 = sim.simxGetObjectHandle(clientID, 'JointRot', sim.simx_opmode_oneshot_wait)
        _, joint4 = sim.simxGetObjectHandle(clientID, 'youBotArmJoint0', sim.simx_opmode_oneshot_wait)
        _, joint5 = sim.simxGetObjectHandle(clientID, 'youBotArmJoint1', sim.simx_opmode_oneshot_wait)
        _, joint6 = sim.simxGetObjectHandle(clientID, 'youBotArmJoint2', sim.simx_opmode_oneshot_wait)
        _, joint7 = sim.simxGetObjectHandle(clientID, 'youBotArmJoint3', sim.simx_opmode_oneshot_wait)
        _, joint8 = sim.simxGetObjectHandle(clientID, 'youBotArmJoint4', sim.simx_opmode_oneshot_wait)
        
        sim.simxSetJointTargetVelocity(clientID, joint1, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint2, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint3, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint4, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint5, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint6, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint7, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint8, 0, sim.simx_opmode_oneshot)
        
        joint_handles = [joint1, joint2, joint3, joint4, joint5, joint6, joint7, joint8]
        
        start_position = [0, 0, 0, math.radians(0), 0, 0, 0, 0]
        end_position = [-0.01, 0.01 ,0.01, math.radians(180), math.radians(0), math.radians(0), math.radians(0), math.radians(0)]

        steps = 50
        interpolated_positions = interpolate(start_position, end_position, steps)        
        
        for positions in interpolated_positions:
            set_joint_positions(clientID, joint_handles, positions)
            time.sleep(0.1)  # Esperar un poco entre pasos
  
        return_code = sim.simxPauseSimulation(clientID, sim.simx_opmode_blocking)
        if return_code == 0:
            print('Simulación pausada')
        else:
            print('Error al pausar la simulación')
        
        # Posiciones y Velocidades inicial y deseada
        velocities_file = "kukaYoubot_Trayectorias\Trayectoria6\QD_kuka.txt"
        position_file = "kukaYoubot_Trayectorias\Trayectoria6\Q_kuka.txt"
        dataVelocity = np.loadtxt(velocities_file)
        dataPosition = np.loadtxt(position_file)
        
        listaVelocities = [vector for vector in dataVelocity]
        listaPositions = [vector for vector in dataPosition]

        # Establecer las posiciones y velocidades interpoladas en los joints
        for velocities in listaVelocities:
            set_joint_velocity(clientID, joint_handles, velocities)
            print("\n Velocities", velocities)
            time.sleep(0.009)  # Trayectoria 6
        # Establecer las posiciones y velocidades interpoladas en los joints
        #for positions in listaPositions:
        #     set_joint_positions(clientID, joint_handles, positions)
        #     print("\n Positions", positions)
        #     time.sleep(0.1)  # Esperar un poco entre pasos
        sim.simxSetJointTargetVelocity(clientID, joint1, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint2, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint3, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint4, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint5, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint6, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint7, 0, sim.simx_opmode_oneshot)
        sim.simxSetJointTargetVelocity(clientID, joint8, 0, sim.simx_opmode_oneshot)
     
        return_code = sim.simxPauseSimulation(clientID, sim.simx_opmode_blocking)
        if return_code == 0:
            print('Simulación pausada')
        else:
            print('Error al pausar la simulación')
            
        # time_values = np.linspace(0, 3, num=50)

        # Llamar a la función para graficar
        # plot_trajectories(time_values, listaPositions, listaVelocities)
        
        time.sleep(0.1)  # Esperar un poco entre pasos
        
        disconnect_from_coppelia(clientID)

if __name__ == '__main__':
    main()
