# Visualisation TP1 - resultats integration
import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# params globaux
plt.rcParams['figure.figsize'] = (10, 6)
plt.rcParams['font.size'] = 11
plt.rcParams['lines.linewidth'] = 1.5
plt.rcParams['lines.markersize'] = 5

FIG_DIR = "figures"
RES_DIR = "resultats"

os.makedirs(FIG_DIR, exist_ok=True)

def q1():
    try:
        data = np.loadtxt(os.path.join(RES_DIR, "q1.csv"), delimiter=',', skiprows=1)
        plt.figure()
        plt.plot(data[:, 0], data[:, 1], 'o-', label='Euler', markersize=4)
        plt.plot(data[:, 0], data[:, 2], '--', label='Analytique', linewidth=2)
        plt.title('Q1 : Désintégration simple - Euler vs Analytique')
        plt.xlabel('Temps (s)')
        plt.ylabel('Densité')
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.savefig(os.path.join(FIG_DIR, "q1.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q1: {e}")

def q2():
    try:
        data = np.loadtxt(os.path.join(RES_DIR, "q2.csv"), delimiter=',', skiprows=1)
        plt.figure()
        plt.plot(data[:, 0], data[:, 1], label='x(t)')
        plt.plot(data[:, 0], data[:, 2], label='y(t)')
        plt.title('Q2 : Désintégration en chaîne')
        plt.xlabel('Temps (s)')
        plt.ylabel('Densité')
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.savefig(os.path.join(FIG_DIR, "q2.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q2: {e}")

def q3():
    try:
        data = np.loadtxt(os.path.join(RES_DIR, "q3.csv"), delimiter=',', skiprows=1)
        plt.figure()
        plt.plot(data[:, 0], data[:, 1])
        plt.title('Q3 : Oscillateur Harmonique')
        plt.xlabel('Temps (s)')
        plt.ylabel('Position')
        plt.grid(True, alpha=0.3)
        plt.savefig(os.path.join(FIG_DIR, "q3.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q3: {e}")

def q8():
    try:
        data = np.loadtxt(os.path.join(RES_DIR, "q8.csv"), delimiter=',', skiprows=1)
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))
        ax1.plot(data[:, 0], data[:, 1], label='x')
        ax1.plot(data[:, 0], data[:, 2], label='y')
        ax1.set_title('Q8 : Évolution temporelle')
        ax1.set_xlabel('Temps (s)')
        ax1.legend()
        ax1.grid(True, alpha=0.3)
        ax2.plot(data[:, 1], data[:, 2])
        ax2.set_title('Q8 : Trajectoire Cyclotron')
        ax2.set_xlabel('x')
        ax2.set_ylabel('y')
        ax2.axis('equal')
        ax2.grid(True, alpha=0.3)
        plt.savefig(os.path.join(FIG_DIR, "q8.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q8: {e}")

def q9():
    try:
        fig, axes = plt.subplots(2, 1, figsize=(12, 8))
        for dt, f in [(0.01, 'q9_dt001.csv'), (0.005, 'q9_dt0005.csv'), (0.001, 'q9_dt0001.csv')]:
            try:
                data = np.loadtxt(os.path.join(RES_DIR, f), delimiter=',', skiprows=1)
                axes[0].plot(data[:, 0], data[:, 3], label=f'Δt={dt}')
                axes[1].semilogy(data[:, 0], np.abs(data[:, 3]), label=f'Δt={dt}')
            except:
                pass
        axes[0].set_title("Q9 : Erreur Euler - différents pas de temps")
        axes[0].set_ylabel('Erreur')
        axes[0].legend()
        axes[0].grid(True, alpha=0.3)
        axes[1].set_xlabel('Temps (s)')
        axes[1].set_ylabel('|Erreur| (log)')
        axes[1].legend()
        axes[1].grid(True, alpha=0.3)
        plt.savefig(os.path.join(FIG_DIR, "q9.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q9: {e}")

def q10():
    try:
        fig, axes = plt.subplots(2, 1, figsize=(12, 8))
        for dt, f in [(0.01, 'q10_dt001.csv'), (0.1, 'q10_dt01.csv'), (0.5, 'q10_dt05.csv')]:
            try:
                data = np.loadtxt(os.path.join(RES_DIR, f), delimiter=',', skiprows=1)
                axes[0].plot(data[:, 0], data[:, 3], label=f'Δt={dt}')
                axes[1].semilogy(data[:, 0], np.abs(data[:, 3]), label=f'Δt={dt}')
            except:
                pass
        axes[0].set_title("Q10 : Erreur RK4 - différents pas de temps")
        axes[0].set_ylabel('Erreur')
        axes[0].legend()
        axes[0].grid(True, alpha=0.3)
        axes[1].set_xlabel('Temps (s)')
        axes[1].set_ylabel('|Erreur| (log)')
        axes[1].legend()
        axes[1].grid(True, alpha=0.3)
        plt.savefig(os.path.join(FIG_DIR, "q10.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q10: {e}")

def q11():
    try:
        fig, axes = plt.subplots(2, 1, figsize=(12, 8))
        for dt, f in [(0.01, 'q11_dt001.csv'), (0.1, 'q11_dt01.csv'), (0.5, 'q11_dt05.csv')]:
            try:
                data = np.loadtxt(os.path.join(RES_DIR, f), delimiter=',', skiprows=1)
                axes[0].plot(data[:, 0], data[:, 3], label=f'Δt={dt}')
                axes[1].semilogy(data[:, 0], np.abs(data[:, 3]), label=f'Δt={dt}')
            except:
                pass
        axes[0].set_title("Q11 : Erreur RK2 - différents pas de temps")
        axes[0].set_ylabel('Erreur')
        axes[0].legend()
        axes[0].grid(True, alpha=0.3)
        axes[1].set_xlabel('Temps (s)')
        axes[1].set_ylabel('|Erreur| (log)')
        axes[1].legend()
        axes[1].grid(True, alpha=0.3)
        plt.savefig(os.path.join(FIG_DIR, "q11.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q11: {e}")

def q12():
    try:
        fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 10))
        colors = {'q9_dt001.csv': 'red', 'q10_dt001.csv': 'green', 'q11_dt001.csv': 'blue'}
        labels = {'q9_dt001.csv': 'Euler', 'q10_dt001.csv': 'RK4', 'q11_dt001.csv': 'RK2'}
        for f, c in colors.items():
            try:
                data = np.loadtxt(os.path.join(RES_DIR, f), delimiter=',', skiprows=1)
                ax1.plot(data[:, 0], data[:, 3], label=labels[f], color=c)
                ax2.semilogy(data[:, 0], np.abs(data[:, 3]), label=labels[f], color=c)
            except:
                pass
        ax1.set_title('Q12 : Comparaison Euler vs RK2 vs RK4 (deltat=0.01s)')
        ax1.set_ylabel('Erreur')
        ax1.legend()
        ax1.grid(True, alpha=0.3)
        ax1.axhline(0, color='k', linestyle='--', alpha=0.3)
        ax2.set_xlabel('Temps (s)')
        ax2.set_ylabel('|Erreur| (log)')
        ax2.legend()
        ax2.grid(True, alpha=0.3)
        plt.savefig(os.path.join(FIG_DIR, "q12.pdf"), dpi=150, bbox_inches='tight')
        plt.close()
    except Exception as e:
        print(f"Erreur Q12: {e}")

def main():
    """Génère tous les graphiques du TP1"""

    for func in [q1, q2, q3, q8, q9, q10, q11, q12]:
        try:
            func()
        except Exception as e:
            print(f"Erreur lors de l'exécution de {func.__name__}: {e}")


if __name__ == "__main__":
    main()
