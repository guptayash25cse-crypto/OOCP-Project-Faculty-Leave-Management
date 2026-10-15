#ifndef FILEMANAGER_H
#define FILEMANAGER_H

class LeaveSystem;

class FileManager {
public:
    void save(const LeaveSystem& system) const;
    void load(LeaveSystem& system) const;
};

#endif
