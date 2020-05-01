class LiPo4SDriverBoardProfile:
    """LiPo4SDriverBoardProfile

    """
    def __init__(self):
        """__init__

        """
        self.gain_cell_1 = -1
        self.offset_cell_1 = -1

        self.gain_cell_2 = -1
        self.offset_cell_2 = -1

        self.gain_cell_3 = -1
        self.offset_cell_3 = -1

        self.gain_cell_4 = -1
        self.offset_cell_4 = -1

        self.filter_rank = -1

    def __str__(self):
        """__str__

            Object's string representation.
        :return: object's string representation
        :rtype: str
        """
        _str = '\nLiPo 4S Driver Board Profile:\n'
        for k, v in self.__dict__.items():
            if not k.startswith('_'):
                _str += '{}: {}\n'.format(k.upper(), v)

        return _str
