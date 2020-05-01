import struct

from logging import getLogger

from lipo_4s_mon.utils.driver_board.profile import LiPo4SDriverBoardProfile
from lipo_4s_mon.utils.interfaces.serial_interface import COMInterface

from lipo_4s_mon import APP_SLUG

LOGGER = getLogger(APP_SLUG)


SIZE_OF_FLOAT = 4
ROUND_PRECISION = 2


class LiPo4SMonitorDriver:
    """LiPo4SMonitorDriver

    """
    def __init__(self, interface):
        """

        :param interface: communication interface
        :type interface: object
        """
        self.interface = interface

    def get_profile(self):
        """get_profile

        :return: profile
        :rtype: LiPo4SDriverBoardProfile
        """
        if isinstance(self.interface, COMInterface):
            return self.get_profile_via_com_interface()
        else:
            LOGGER.info('Invalid driver interface type: {}'.format(type(self.interface)))
            return False

    def get_profile_via_com_interface(self):
        """get_profile_via_com_interface

        :return: profile
        :rtype: LiPo4SDriverBoardProfile
        """
        assert isinstance(self.interface, COMInterface)
        self.interface.send_data(10)
        received_data = self.interface.receive_data(35)

        profile = LiPo4SDriverBoardProfile()

        if not received_data:
            return profile

        received_data = [raw_data for raw_data in received_data][2:]  # remove first 2 received bytes: LF and CR

        profile.filter_rank = received_data[-1]
        received_data = received_data[:-1]

        profile.offset_cell_1 = round(struct.unpack('f', bytes(received_data[:SIZE_OF_FLOAT]))[0], ROUND_PRECISION)
        received_data = received_data[SIZE_OF_FLOAT:]

        profile.gain_cell_1 = round(struct.unpack('f', bytes(received_data[:SIZE_OF_FLOAT]))[0], ROUND_PRECISION)
        received_data = received_data[SIZE_OF_FLOAT:]

        profile.offset_cell_2 = round(struct.unpack('f', bytes(received_data[:SIZE_OF_FLOAT]))[0], ROUND_PRECISION)
        received_data = received_data[SIZE_OF_FLOAT:]

        profile.gain_cell_2 = round(struct.unpack('f', bytes(received_data[:SIZE_OF_FLOAT]))[0], ROUND_PRECISION)
        received_data = received_data[SIZE_OF_FLOAT:]

        profile.offset_cell_3 = round(struct.unpack('f', bytes(received_data[:SIZE_OF_FLOAT]))[0], ROUND_PRECISION)
        received_data = received_data[SIZE_OF_FLOAT:]

        profile.gain_cell_3 = round(struct.unpack('f', bytes(received_data[:SIZE_OF_FLOAT]))[0], ROUND_PRECISION)
        received_data = received_data[SIZE_OF_FLOAT:]

        profile.offset_cell_4 = round(struct.unpack('f', bytes(received_data[:SIZE_OF_FLOAT]))[0], ROUND_PRECISION)
        received_data = received_data[SIZE_OF_FLOAT:]

        profile.gain_cell_4 = round(struct.unpack('f', bytes(received_data[:SIZE_OF_FLOAT]))[0], ROUND_PRECISION)

        return profile
