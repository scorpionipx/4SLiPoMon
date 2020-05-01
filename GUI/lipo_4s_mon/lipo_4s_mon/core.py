from lipo_4s_mon.utils.driver_board.driver import LiPo4SMonitorDriver
from lipo_4s_mon.utils.interfaces.serial_interface import COMInterface


class LiPo4SMonitor:
    """LiPo4SMonitor

    """
    def __init__(self, communication_interface):
        """__init__

        :param communication_interface: driver board communication interface instance
        """
        self.driver = LiPo4SMonitorDriver(interface=communication_interface)

    def get_profile(self):
        """

        :return:
        """
        return self.driver.get_profile()


interface = COMInterface()
interface.connect(com_port=4)

lipo_4s_mon = LiPo4SMonitor(communication_interface=interface)
profile = lipo_4s_mon.get_profile()
print(profile)
